#ifndef KNNTHREAD_H
#define KNNTHREAD_H

#include "knn.h"
#include "Element.h"

#include<QThread>
#include<QMapIterator>

class MetricInterface;

class KnnThread: public QThread
{
public:
    KnnThread(const QVector<Element> &elementsVector, int, int, QString, int, QList<QPair<int, int> >*, const MetricInterface *metric);
    void run();

private:
    const QVector<Element> mElementsVector;
    const int index1;
    const int index2;
    const MetricInterface *mMetric;
    const QString name;
    const int numThreads;
    QList<QPair<int, int> > *resultList;
};

#endif // KNNTHREAD_H
