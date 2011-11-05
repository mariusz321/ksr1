#include "ArticleLoader.h"
#include "DiscriminatingExtractor.h"

#include <QtCore/QCoreApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if (a.arguments().size() < 2) {
        qFatal("usage: %s [input file]\n", argv[0]);
    }
    
    const QList<QPair<QString, QString> > articles = ArticleLoader::loadFromFile(a.arguments().at(1));
    KeywordExtractorInterface *kwi = new DiscriminatingExtractor();
    const QList<QPair<QString, double> > kw = kwi->extractKeywords(articles);
    delete kwi;
    for (int i = 0; i < kw.size(); i++) {
        qDebug() << kw.at(i).first << kw.at(i).second;
    }

    return 0;
}
