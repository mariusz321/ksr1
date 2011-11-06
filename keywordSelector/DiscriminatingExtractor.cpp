#undef __STRICT_ANSI__
#include "DiscriminatingExtractor.h"

#include <QElapsedTimer>

#include <QDebug>

// uncomment the define below for timings
//#define TIMING

QList<QPair<QString, kwreal> > DiscriminatingExtractor::extractKeywords(const QList<QPair<QString, QString> > &articles) const
{
    QList<QPair<QString, kwreal> > result;
    QVector<QSet<QString> > articlesWords;
    QSet<QString> allWords;
    articlesWords.reserve(articles.size());
    QRegExp wordExtractor("\\b(\\w+)\\b", Qt::CaseInsensitive);
    QRegExp numbers("[0-9]");
    for (int i = 0; i < articles.size(); i++) {
        int pos = 0;
        QSet<QString> articleWords;
        const QString &str = articles.at(i).second;
        while ((pos = wordExtractor.indexIn(str, pos)) != -1) {
            QString word = wordExtractor.cap();
            word.remove(numbers);
            if (word.length() > 2) {    // there's no point in storing 'I', 'a', ...
                articleWords.insert(word);
            }
            pos += wordExtractor.matchedLength();
        }
        articlesWords.append(articleWords);
    }

    for (int i = 0; i < articlesWords.size(); i++) {
        allWords.unite(articlesWords.at(i));
    }
    QHash<QString, int> decimator;
    decimator.reserve(allWords.size());
    for (int i = 0; i < articlesWords.size(); i++) {
        for (int j = 0; j < articlesWords.at(i).size(); j++) {
            decimator[articlesWords.at(i).values().at(j)]++;
        }
    }
    int threshold = 0.6 * articles.size();
    for (int i = 0; i < decimator.size(); i++) {
        if (decimator.values().at(i) >= threshold) {
            const QString key = decimator.keys().at(i);
            for (int j = 0; j < articlesWords.size(); j++) {
                articlesWords[j].remove(key);
            }
            allWords.remove(key);
        }
    }
#if 0
    QStringList listall;
    listall.reserve(allWords.size());
    for (int i = 0; i < allWords.size(); i++) {
        listall << allWords.values().at(i);
    }
    qSort(listall);
    qDebug() << listall;
    qDebug() << listall.size();
    return result;
#endif
    const kwreal g = getSimiliarity(articlesWords);
    qDebug() << "g:" << g;
    kwreal *sortBuf = new kwreal[allWords.size()];
#pragma omp parallel for
    for (int i = 0; i < allWords.size(); i++) {
#ifdef TIMING
        QElapsedTimer timer;
        timer.start();
        int subMsecs;
        int simMsecs;
#endif
        QVector<QSet<QString> > subtractedWords = articlesWords;
        for (int j = 0; j < subtractedWords.size(); j++) {
            subtractedWords[j].remove(allWords.values().at(i));
        }
#ifdef TIMING
        subMsecs = timer.restart();
#endif
        sortBuf[i] = getSimiliarity(subtractedWords);
#ifdef TIMING
        simMsecs = timer.elapsed();
        qDebug() << "i:" << i << "subtraction:" << subMsecs << "similiarity:" << simMsecs;
#endif
    }
    QList<QPair<kwreal, QString> > sortList;
    sortList.reserve(allWords.size());
    for (int i = 0; i < allWords.size(); i++) {
        sortList.append(qMakePair(sortBuf[i] - g, allWords.values().at(i)));
    }
    delete [] sortBuf;
    qSort(sortList);
    result.reserve(sortList.size());
    foreach (const auto pair, sortList) {
        result.append(qMakePair(pair.second, pair.first));
    }
    return result;
}

kwreal DiscriminatingExtractor::getSimiliarity(const QVector<QSet<QString> > &articlesWords) const
{
    const int size = articlesWords.size();
    kwreal sum = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            QSet<QString> intersected = articlesWords.at(i);
            intersected.intersect(articlesWords.at(j));
            QSet<QString> united = articlesWords.at(i);
            united.unite(articlesWords.at(j));
            sum += kwreal(intersected.size()) / kwreal(united.size());
        }
    }
    sum *= 2;
    return sum;
}
