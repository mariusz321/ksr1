#ifndef ARTICLELOADER_H
#define ARTICLELOADER_H

#include <QList>
#include <QPair>

class QIODevice;

class ArticleLoader
{
public:
    static QList<QPair<QString, QString> > loadFromFile(const QString &fileName);
    static QList<QPair<QString, QString> > loadArticles(QIODevice *input);
};

#endif // ARTICLELOADER_H
