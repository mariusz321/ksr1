#include "VectorLoader.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>

QVector<Element> VectorLoader::loadData(const QStringList &arguments)
{
    const QString fileName(arguments.at(0));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QVector<Element> result;

    while (!in.atEnd()) {
        Element e;
        e.label = in.readLine();

        QString line = in.readLine();
        line.remove(QRegExp("\\[|\\]"));
        QStringList stringList = line.split(";");
        QVector<double> *vect = new QVector<double>(stringList.size());
        for(int i =0; i<stringList.size(); i++){
            (*vect)[i] = stringList.at(i).toDouble();
        }
        e.features = vect;
        result.append(e);
    }
    return result;
}

void VectorLoader::clean(const QVector<Element> &elements)
{
    for (int i = 0; i < elements.size(); i++) {
        delete elements.at(i).features;
    }
}
