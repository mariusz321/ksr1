#ifndef KNNSIMILARITYTHREAD_H
#define KNNSIMILARITYTHREAD_H

#include<QThread>
#include<QSet>
#include<QMapIterator>
#include "knn.h"

class KnnSimilarityThread: public QThread
{
public:
    KnnSimilarityThread(QList<QSet<QString> >, QSet<QString>, QList<QString>, int, int, Knn, QString, int, QList<QPair<int, int> >*);
    void run();

private:
    QList<QSet<QString> > wordSetList;
    QList<QString> labelsList;
    QSet<QString> allWordsSet;
    int index1;
    int index2;
    Knn knn;
    QString name;
    int numThreads;
    QList<QPair<int, int> > *resultList;
};


#endif // KNNSIMILARITYTHREAD_H
