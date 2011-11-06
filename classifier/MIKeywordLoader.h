#ifndef MIKEYWORDLOADER_H
#define MIKEYWORDLOADER_H

#include "KeywordLoaderInterface.h"

class MIKeywordLoader : public KeywordLoaderInterface
{
public:
    QList<QPair<QString, QStringList> > loadKeywords(QIODevice *dev) const;
};

#endif // MIKEYWORDLOADER_H
