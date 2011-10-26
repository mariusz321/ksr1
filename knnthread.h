#ifndef TEST_H
#define TEST_H

#include<QThread>
#include<QMapIterator>
#include "knn.h"

class KnnThread: public QThread
{
public:
    KnnThread(QList<QVector<double> >, QList<QString>, int, int, Knn, QString, int, QList<QPair<int, int> >*);
    void run();

private:
    QList<QVector<double> > vectorList;
    QList<QString> labelsList;
    int index1;
    int index2;
    Knn knn;
    QString name;
    int numThreads;
    QList<QPair<int, int> > *resultList;
};

#endif // TEST_H
