#ifndef MIEXTRACTOR_H
#define MIEXTRACTOR_H

#include "KeywordExtractorInterface.h"

class MIExtractor : public KeywordExtractorInterface
{
public:
    QList<QPair<QString, QList<QPair<kwreal, QString> > > > extractKeywords(const QList<QPair<QString, QString> > &articles) const;
};

#endif // MIEXTRACTOR_H
