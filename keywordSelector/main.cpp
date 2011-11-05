#include "ArticleLoader.h"
#include "DiscriminatingExtractor.h"

#include <QtCore/QCoreApplication>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    const QList<QPair<QString, QString> > articles = ArticleLoader::loadFromFile("test.dat");
    KeywordExtractorInterface *kwi = new DiscriminatingExtractor();
    const QList<QPair<QString, double> > kw = kwi->extractKeywords(articles);
    delete kwi;
    for (int i = 0; i < kw.size(); i++) {
        qDebug() << kw.at(i).first << kw.at(i).second;
    }

    return 0;
}
