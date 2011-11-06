#undef __STRICT_ANSI__
#include "ArticleLoader.h"
#include "DiscriminatingExtractor.h"
#include "MIExtractor.h"

#include <QtCore/QCoreApplication>
#include <QTextStream>
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
#include <QElapsedTimer>
#endif

#include <QDebug>
#include <QFile>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    if (a.arguments().size() < 3) {
        qFatal("usage: %s [input file] [output file] [start index] [stop index] [g]\n", argv[0]);
    }
    if (a.arguments().size() >= 4) {
        bool ok;
        a.arguments().at(3).toInt(&ok);
        if (!ok) {
            qFatal("failed parsing argument 3\n");
        }
    }
    if (a.arguments().size() >= 5) {
        bool ok;
        a.arguments().at(4).toInt(&ok);
        if (!ok) {
            qFatal("failed parsing argument 4\n");
        }
    }
    if (a.arguments().size() >= 6) {
        bool ok;
        a.arguments().at(5).toDouble(&ok);
        if (!ok) {
            qFatal("failed parsing argument 5\n");
        }
    }
    
    QList<QPair<QString, QString> > articles;
    QList<QPair<QString, kwreal> > kw;

    // limit the scope of timer
    {
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
        QElapsedTimer loadTimer;
        loadTimer.start();
#endif
        articles = ArticleLoader::loadFromFile(a.arguments().at(1));
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
        int loadMsecs = loadTimer.elapsed();
        qDebug() << "loading took" << loadMsecs << "msecs";
#endif
    }
    KeywordExtractorInterface *kwi = new MIExtractor();
    {
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
        QElapsedTimer extractTimer;
        extractTimer.start();
#endif
        kw = kwi->extractKeywords(articles);
#if QT_VERSION >= QT_VERSION_CHECK(4, 7, 0)
        int extractMsecs = extractTimer.elapsed();
        qDebug() << "extraction took" << extractMsecs << "msecs";
#endif
    }
    delete kwi;
    QFile file(a.arguments().at(2));
    if(file.open(QIODevice::WriteOnly)){
            QTextStream out(&file);
            for (int i = 0; i < kw.size(); i++) {
                //qDebug() << kw.at(i).second << kw.at(i).first;
                out << kw.at(i).second << " " << kw.at(i).first << endl;
            }
    }
    file.close();

    return 0;
}
