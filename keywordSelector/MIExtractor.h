#ifndef MIEXTRACTOR_H
#define MIEXTRACTOR_H

#include "KeywordExtractorInterface.h"

class MIExtractor : public KeywordExtractorInterface
{
public:
    QList<QPair<QString, kwreal> > extractKeywords(const QList<QPair<QString, QString> > &articles) const;
};

#endif // MIEXTRACTOR_H
