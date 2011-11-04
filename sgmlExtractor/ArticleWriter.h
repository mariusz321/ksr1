#ifndef ARTICLEWRITER_H
#define ARTICLEWRITER_H

#include <QPair>

class QIODevice;

class ArticleWriter
{
public:
    static void saveArticles(QIODevice *out, const QList<QPair<QString, QString> > &articles);
};

#endif // ARTICLEWRITER_H
