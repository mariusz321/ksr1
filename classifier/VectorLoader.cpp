#undef __STRICT_ANSI__
#include "VectorLoader.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <cmath>
#include <QDebug>

QVector<Element> VectorLoader::loadData(const QStringList &arguments, const bool &normalize)
{
    const QString fileName(arguments.at(0));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QVector<Element> result;

    int count = 1;
    while (!in.atEnd()) {
        Element e;
        e.label = in.readLine();

        QString line = in.readLine();
        line.remove(QRegExp("\\[|\\]"));
        QStringList stringList = line.split(";");
        QVector<double> *vect = new QVector<double>(stringList.size());
        double  length = 0;
        for(int i =0; i<stringList.size(); i++){
            (*vect)[i] = stringList.at(i).toDouble();
            if(normalize){
                length += (*vect)[i]*(*vect)[i];
            }
        }
        if(normalize){
            length = sqrt(length);
            for(int i=0; i<vect->size(); i++){
                (*vect)[i]/=length;
            }
        }
        e.features = vect;
        result.append(e);

        qDebug()<<"Read: "<<count;
        count++;
    }
    file.close();
    return result;
}

void VectorLoader::clean(const QVector<Element> &elements)
{
    for (int i = 0; i < elements.size(); i++) {
        delete elements.at(i).features;
    }
}
