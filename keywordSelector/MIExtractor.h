#ifndef MIEXTRACTOR_H
#define MIEXTRACTOR_H

#include "KeywordExtractorInterface.h"

class MIExtractor : public KeywordExtractorInterface
{
public:
    QVector<QPair<QString, QVector<QPair<kwreal, QString> > > > extractKeywords(const QList<QPair<QString, QString> > &articles) const;
};

#endif // MIEXTRACTOR_H
