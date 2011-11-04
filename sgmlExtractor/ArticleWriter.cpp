#include "ArticleWriter.h"

#include <QTextStream>

void ArticleWriter::saveArticles(QIODevice *_out, const QList<QPair<QString, QString> > &articles)
{
    QTextStream out(_out);
    foreach (const auto &article, articles) {
        out << article.first << endl;
        out << article.second << endl;
    }
}
