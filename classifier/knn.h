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

    QList<QString> labelsList;

    void initLabels(QList<QPair<QString, QString> >);
    double normalizedDistance(const QVector<double>&, const QVector<double>&) const;
    double jaccardSimilarity(QSet<QString>, QSet<QString>);
    double newSimilarity(QSet<QString>, QSet<QString>, QSet<QString>, QSet<QString>);
    double ngramSimilarity(QSet<QString>, QSet<QString>);
    void testDistance(QTextStream &);
    void testSimilarity(QTextStream &, QList<QSet<QString> >, QSet<QString>);
    void format(QTextStream &out, int k, int success, int failure) const;
};

#endif // KNN_H
