#ifndef KNN_H
#define KNN_H

#include<QPair>
#include<QFile>
#include<QTextStream>
#include<QRegExp>
#include<QStringList>
#include<QVector>
#include<QList>
#include<QSet>
#include<QElapsedTimer>

class Knn
{
public:
    Knn();

    QList<QVector<double> > vectorsList;
    QList<QString> labelsList;

    void readVetors(QString);
    void initLabels(QList<QPair<QString, QString> >);
    double euclideanDistance(QVector<double>, QVector<double>);
    double manhattanDistance(const QVector<double>&, const QVector<double>&) const;
    double chebyshevDistance(const QVector<double>&, const QVector<double>&) const;
    double normalizedDistance(const QVector<double>&, const QVector<double>&) const;
    double jaccardSimilarity(QSet<QString>, QSet<QString>);
    double smcSimilarity(QSet<QString>, QSet<QString>, QSet<QString>);
    void testDistance(QTextStream &);
    void testSimilarity(QTextStream &, QList<QSet<QString> >, QSet<QString>);
};

#endif // KNN_H
