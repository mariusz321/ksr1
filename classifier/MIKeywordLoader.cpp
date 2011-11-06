#include "MIKeywordLoader.h"

#include <QTextStream>

#include <QDebug>

QList<QPair<QString, QStringList> > MIKeywordLoader::loadKeywords(QIODevice *dev) const
{
    QHash<QString, QStringList> keywordsHash;
    QTextStream in(dev);
    QString label;
    QRegExp labelCapture("\\*\\*\\* (.+) \\*\\*\\*");
    while (!in.atEnd()) {
        const QString line = in.readLine();
        if (labelCapture.indexIn(line) != -1) {
            label = labelCapture.cap(0);
            qDebug() << label;
        } else {
            const QStringList kwline = line.split(' ', QString::SkipEmptyParts);
            if (kwline.size() == 2) {
                keywordsHash[label].append(kwline.at(1));
            }
        }
    }
    QList<QPair<QString, QStringList> > result;
    for (int i = 0; i < keywordsHash.size(); i++) {
        result.append(qMakePair(keywordsHash.keys().at(i), keywordsHash.values().at(i)));
    }
    return result;
}
