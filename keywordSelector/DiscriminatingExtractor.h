#ifndef DISCRIMINATINGEXTRACTOR_H
#define DISCRIMINATINGEXTRACTOR_H

#include "KeywordExtractorInterface.h"

class DiscriminatingExtractor : public KeywordExtractorInterface
{
public:
   QList<QPair<QString, kwreal> > extractKeywords(const QList<QPair<QString, QString> > &articles) const;
   kwreal getSimiliarity(const QVector<QSet<QString> > &articlesWords) const;
   kwreal getSimiliarity(const QVector<QSet<int> > &articlesWords) const;
};

#endif // DISCRIMINATINGEXTRACTOR_H
