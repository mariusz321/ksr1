#ifndef KNNTHREAD_H
#define KNNTHREAD_H

#include<QThread>
#include<QMapIterator>
#include "knn.h"

class KnnThread: public QThread
{
public:
    KnnThread(const QList<QVector<double> > &, const QList<QString> &, int, int, Knn &, QString, int, QList<QPair<int, int> >*);
    void run();

private:
    const QList<QVector<double> > vectorList;
    const QList<QString> labelsList;
    const int index1;
    const int index2;
    Knn knn;
    const QString name;
    const int numThreads;
    QList<QPair<int, int> > *resultList;
};

#endif // KNNTHREAD_H
