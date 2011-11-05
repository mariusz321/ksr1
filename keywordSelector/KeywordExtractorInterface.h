#ifndef KEYWORDEXTRACTORINTERFACE_H
#define KEYWORDEXTRACTORINTERFACE_H

#include <QStringList>
#include <QPair>

typedef float kwreal;

class KeywordExtractorInterface
{
public:
    virtual QList<QPair<QString, kwreal> > extractKeywords(const QList<QPair<QString, QString> > &articles) const = 0;
};

#endif // KEYWORDEXTRACTORINTERFACE_H
