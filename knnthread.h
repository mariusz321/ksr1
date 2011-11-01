#ifndef TEST_H
#define TEST_H

#include<QThread>
#include<QMapIterator>
#include "knn.h"

class KnnThread: public QThread
{
public:
    KnnThread(const QList<QVector<double> > &, const QList<QString> &, int, int, const Knn &, QString, int, QList<QPair<int, int> >*);
    void run();

private:
    const QList<QVector<double> > vectorList;
    const QList<QString> labelsList;
    const int index1;
    const int index2;
    const Knn knn;
    const QString name;
    const int numThreads;
    QList<QPair<int, int> > *resultList;
};

#endif // TEST_H
