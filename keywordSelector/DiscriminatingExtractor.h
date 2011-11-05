#ifndef DISCRIMINATINGEXTRACTOR_H
#define DISCRIMINATINGEXTRACTOR_H

#include "KeywordExtractorInterface.h"

class DiscriminatingExtractor : public KeywordExtractorInterface
{
public:
   QList<QPair<QString, double> > extractKeywords(const QList<QPair<QString, QString> > &articles) const;
   double getSimiliarity(const QVector<QSet<QString> > &articlesWords) const;
};

#endif // DISCRIMINATINGEXTRACTOR_H
