#ifndef KNN_H
#define KNN_H

#include<QPair>
#include<QFile>
#include<QTextStream>
#include<QRegExp>
#include<QStringList>
#include<QVector>
#include<QList>
#include<QElapsedTimer>

class Knn
{
public:
    Knn();

    QList<QVector<double> > vectorsList;
    QList<QString> labelsList;

    void readVetors(QString);
    double euclideanDistance(QVector<double>, QVector<double>);
    double manhattanDistance(QVector<double>, QVector<double>);
    double chebyshevDistance(QVector<double>, QVector<double>);
    double normalizedDistance(QVector<double>, QVector<double>);
    void test(QTextStream &);
};

#endif // KNN_H
