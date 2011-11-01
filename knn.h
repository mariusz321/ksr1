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
    double euclideanDistance(const QVector<double> &, const QVector<double> &) const;
    double manhattanDistance(const QVector<double> &, const QVector<double> &) const;
    double chebyshevDistance(const QVector<double> &, const QVector<double> &) const;
    double normalizedDistance(const QVector<double> &, const QVector<double> &) const;
    void test(QTextStream &);
};

#endif // KNN_H
