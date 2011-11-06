#include "KeywordLoaderInterface.h"

#include <QFile>

QList<QPair<QString, QStringList> > KeywordLoaderInterface::loadFromFile(const QString &filename) const
{
    QFile f(filename);
    if (!f.open(QIODevice::ReadOnly)) {
        qFatal("failed to open %s\n", filename.toStdString().c_str());
    }
    QList<QPair<QString, QStringList> > result = loadKeywords(&f);
    f.close();
    return result;
}
