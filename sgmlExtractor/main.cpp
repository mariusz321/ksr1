#undef __STRICT_ANSI__
#include "SgmlReader.h"
#include "ArticleWriter.h"

#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    QStringList labelsList;
    labelsList.append("COFFEE");
    labelsList.append("GOLD");
    labelsList.append("SHIP");
    labelsList.append("SUGAR");

    QString tag = "TOPICS";
    QString dirName = QString("texts");

    SgmlReader sgmlReader = SgmlReader(labelsList, tag);
    const QList<QPair<QString, QString> > labelsArticlesPairs = sgmlReader.readDirectory(dirName);
    const QString fileName("output.dat");
    QFile output(fileName);
    if (!output.open(QIODevice::WriteOnly)) {
        qFatal("Failed to open file %s!\n", fileName.toStdString().c_str());
    }
    ArticleWriter::saveArticles(&output, labelsArticlesPairs);
    output.close();

    return 0;
}
