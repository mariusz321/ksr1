#ifndef KEYWORDLOADERINTERFACE_H
#define KEYWORDLOADERINTERFACE_H

#include <QStringList>
#include <QPair>

class KeywordLoaderInterface
{
public:
    virtual QList<QPair<QString, QStringList> > loadKeywords(QIODevice *dev) const = 0;
    QList<QPair<QString, QStringList> > loadFromFile(const QString &filename) const;
};

#endif // KEYWORDLOADERINTERFACE_H
