#undef __STRICT_ANSI__
#include "DiscriminatingExtractor.h"

#include <QCoreApplication>

#include <QDebug>

// uncomment the define below for timings
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
    //#define TIMING
    #ifdef TIMING
        #include <QElapsedTimer>
    #endif
#endif

QVector<QPair<QString, QVector<QPair<kwreal, QString> > > > DiscriminatingExtractor::extractKeywords(const QList<QPair<QString, QString> > &articles) const
{
    QVector<QPair<QString, QVector<QPair<kwreal, QString> > > > result;
    QVector<QSet<QString> > articlesWords;
    QVector<QSet<int> > articlesWordsInt;
    QSet<QString> allWords;
    articlesWords.reserve(articles.size());
    articlesWordsInt.reserve(articles.size());
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
    QList<QString> wordToIntMapList = allWords.toList();
    for (int i = 0; i < articlesWords.size(); i++) {
        QSet<int> articleWordsInt;
        articleWordsInt.reserve(articlesWords.at(i).size());
        for (int j = 0; j < articlesWords.at(i).size(); j++) {
            articleWordsInt.insert(wordToIntMapList.indexOf(articlesWords.at(i).values().at(j)));
        }
        articlesWordsInt.append(articleWordsInt);
    }
#if 1
    QStringList listall;
    listall.reserve(allWords.size());
    for (int i = 0; i < allWords.size(); i++) {
        listall << allWords.values().at(i);
    }
    qSort(listall);
    qDebug() << listall;
    qDebug() << listall.size();
#endif
    const QStringList args(QCoreApplication::instance()->arguments());
    kwreal argg = 0;
    if (args.size() >= 6) {
        argg = args.at(5).toDouble();
    }
    const kwreal g = (argg == 0) ? getSimiliarity(articlesWords) : argg;
    qDebug() << "g:" << g;
    kwreal *sortBuf = new kwreal[allWords.size()];
    int start = 0;
    int end = allWords.size();
    if (args.size() >= 5) {
        start = args.at(3).toInt();
        end = qMin(args.at(4).toInt(), allWords.size());
    }
#pragma omp parallel for
    for (int i = start; i < end; i++) {
#ifdef TIMING
        QElapsedTimer timer;
        timer.start();
        int subMsecs;
        int simMsecs;
#endif
        QVector<QSet<int> > subtractedWords = articlesWordsInt;
        for (int j = 0; j < subtractedWords.size(); j++) {
            subtractedWords[j].remove(i);
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
    QVector<QPair<kwreal, QString> > sortVector;
    sortVector.reserve(allWords.size());
    for (int i = 0; i < allWords.size(); i++) {
        sortVector.append(qMakePair(sortBuf[i] - g, allWords.values().at(i)));
    }
    delete [] sortBuf;
    qSort(sortVector);
    result.append(qMakePair(QString("GLOBAL"), sortVector));
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

kwreal DiscriminatingExtractor::getSimiliarity(const QVector<QSet<int> > &articlesWords) const
{
    const int size = articlesWords.size();
    kwreal sum = 0;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            QSet<int> intersected = articlesWords.at(i);
            intersected.intersect(articlesWords.at(j));
            QSet<int> united = articlesWords.at(i);
            united.unite(articlesWords.at(j));
            sum += kwreal(intersected.size()) / kwreal(united.size());
        }
    }
    sum *= 2;
    return sum;
}
