#include "DiscriminatingExtractor.h"

#include <QDebug>

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
        QVector<QSet<QString> > subtractedWords = articlesWords;
        for (int j = 0; j < subtractedWords.size(); j++) {
            subtractedWords[j].remove(allWords.values().at(i));
        }
        sortBuf[i] = getSimiliarity(subtractedWords);
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
