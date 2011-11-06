#include "MIExtractor.h"

#include <QString>
#include <QSet>
#include <QVector>
#include <cmath>

#include <QDebug>

QList<QPair<QString, kwreal> > MIExtractor::extractKeywords(const QList<QPair<QString, QString> > &articles) const
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

    const QStringList &allWordsList = allWords.values();
    const QStringList &allClassesList = allClasses.values();
    const float N = articles.size();
    for (int i = 0; i < allClassesList.size(); i++) {
        QList<QPair<kwreal, QString> > classKeywordsList;
        for (int j = 0; j < allWordsList.size(); j++) {
            const QString &word = allWordsList.at(j);
            int N11 = 0, N10 = 0, N01 = 0, N00 = 0;
            for (int k = 0; k < articlesWords.size(); k++) {
                const bool classMatched = (articles.at(k).first == allClassesList.at(i));
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
            classKeywordsList.append(qMakePair(sum, word));
        }
        qSort(classKeywordsList);
        const int count = 10;
        qDebug() << "class" << allClassesList.at(i);
        for (int j = classKeywordsList.size() - 1; j >= classKeywordsList.size() - count; j--) {
            qDebug() << classKeywordsList.at(j).first << classKeywordsList.at(j).second;
        }
    }

    QList<QPair<QString, kwreal> > result;
    return result;
}
