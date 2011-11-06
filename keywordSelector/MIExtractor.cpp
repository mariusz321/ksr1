#include "MIExtractor.h"

#include <QString>
#include <QSet>
#include <QVector>
#include <cmath>

#include <QDebug>

QVector<QPair<QString, QVector<QPair<kwreal, QString> > > > MIExtractor::extractKeywords(const QList<QPair<QString, QString> > &articles) const
{
    QSet<QString> allWords;
    QSet<QString> allClasses;
    QVector<QSet<QString> > articlesWords;
    articlesWords.reserve(articles.size());
    QRegExp wordExtractor("\\b(\\w+)\\b", Qt::CaseInsensitive);
    QRegExp numbers("[0-9]");
    for (int i = 0; i < articles.size(); i++) {
        int pos = 0;
        QSet<QString> articleWords;
        allClasses.insert(articles.at(i).first);
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

    QVector<QPair<QString, QVector<QPair<kwreal, QString> > > > result(allClasses.size());
    const QVector<QString> allWordsVector = allWords.values().toVector();
    const QVector<QString> allClassesVector = allClasses.values().toVector();
    const float N = articles.size();
    const QString *wordsConstPtr = allWordsVector.constData();
    const QString *classesConstPtr = allClassesVector.constData();
    for (int i = 0; i < allClassesVector.size(); i++) {
        QVector<QPair<kwreal, QString> > classKeywordsVector(allWordsVector.size());
        QPair<kwreal, QString> *keywordsPtr = classKeywordsVector.data();
#pragma omp parallel for
        for (int j = 0; j < allWordsVector.size(); j++) {
            const QString &word = wordsConstPtr[j];
            int N11 = 0, N10 = 0, N01 = 0, N00 = 0;
            for (int k = 0; k < articlesWords.size(); k++) {
                const bool classMatched = (articles.at(k).first == classesConstPtr[i]);
                if (articlesWords.at(k).contains(word)) {
                    if (classMatched) {
                        ++N11;
                    } else {
                        ++N10;
                    }
                } else {
                    if (classMatched) {
                        ++N01;
                    } else {
                        ++N00;
                    }
                }
            }
            if (N11 == 0 || N01 == 0 || N10 == 0 || N00 == 0) {
                continue;
            }
            const kwreal fN00 = N00;
            const kwreal fN01 = N01;
            const kwreal fN10 = N10;
            const kwreal fN11 = N11;
            kwreal sum;
            sum  = fN11 / N * log2(N * fN11 / ((fN10 + fN11) * (fN01 + fN11)));
            sum += fN01 / N * log2(N * fN01 / ((fN01 + fN00) * (fN01 + fN11)));
            sum += fN10 / N * log2(N * fN10 / ((fN10 + fN11) * (fN10 + fN00)));
            sum += fN00 / N * log2(N * fN00 / ((fN10 + fN00) * (fN01 + fN00)));
            keywordsPtr[j] = qMakePair(sum, word);
        }
        qSort(classKeywordsVector);
        result[i] = (qMakePair(classesConstPtr[i], classKeywordsVector));
    }

    return result;
}
