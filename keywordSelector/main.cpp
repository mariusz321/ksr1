#undef __STRICT_ANSI__
#include "ArticleLoader.h"
#include "DiscriminatingExtractor.h"

#include <QtCore/QCoreApplication>
#include <QTextStream>
#include <QElapsedTimer>

#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if (a.arguments().size() < 2) {
        qFatal("usage: %s [input file]\n", argv[0]);
    }
    
    QList<QPair<QString, QString> > articles;
    QList<QPair<QString, kwreal> > kw;

    // limit the scope of timer
    {
        QElapsedTimer loadTimer;
        loadTimer.start();
        articles = ArticleLoader::loadFromFile(a.arguments().at(1));
        int loadMsecs = loadTimer.elapsed();
        qDebug() << "loading took" << loadMsecs << "msecs";
    }
    KeywordExtractorInterface *kwi = new DiscriminatingExtractor();
    {
        QElapsedTimer extractTimer;
        extractTimer.start();
        kw = kwi->extractKeywords(articles);
        int extractMsecs = extractTimer.elapsed();
        qDebug() << "extraction took" << extractMsecs << "msecs";
    }
    delete kwi;
    QFile file("keyword.txt");
    if(file.open(QIODevice::WriteOnly)){
            QTextStream out(&file);
            for (int i = 0; i < kw.size(); i++) {
                qDebug() << kw.at(i).first << kw.at(i).second;
                out<<kw.at(i).first << kw.at(i).second<<endl;
            }
    }


    return 0;
}