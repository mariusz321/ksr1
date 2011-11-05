#include "ArticleLoader.h"

#include <QTextStream>
#include <QFile>
#include <QDebug>

QList<QPair<QString, QString> > ArticleLoader::loadArticles(QIODevice *input)
{
    QList<QPair<QString, QString> > result;
    QTextStream in(input);
    while (!in.atEnd()) {
        const QString label(in.readLine());
        const QString article(in.readLine());
        result.append(qMakePair(label, article));
    }
    return result;
}


QList<QPair<QString, QString> > ArticleLoader::loadFromFile(const QString &fileName)
{
    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly)) {
        qFatal("Failed to open %s\n", fileName.toStdString().c_str());
    }
    QList<QPair<QString, QString> > result = loadArticles(&f);
    f.close();
    return result;
}
