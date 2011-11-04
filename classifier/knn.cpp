#include "knn.h"
#include <cmath>
#include <iostream>
#include "knnthread.h"
#include "knnsimilaritythread.h"
#include "MetricInterface.h"
#include "MetricFactory.h"

Knn::Knn()
{

}

void Knn::initLabels(QList<QPair<QString, QString> > labelsArticlesPairs){
    labelsList = QList<QString>();
    labelsList.reserve(labelsArticlesPairs.size());
    foreach(const auto labelArticlePair, labelsArticlesPairs){
        labelsList.append(labelArticlePair.first);
    }

}

void Knn::testDistance(QTextStream &out){

    int NUM_THREADS = QThread::idealThreadCount();

    QList<QList<QPair<int, int> > *> resultList;
    for(int i=0; i<NUM_THREADS; i++){
        resultList.append(new QList<QPair<int, int> >());
    }

    MetricInterface *metric = MetricFactory::getNewMetric("euclidean");

    const QVector<Element> elements = metric->loadData(QStringList() << "wektory.txt");

    int index = floor(elements.size()*0.6);

    QList<KnnThread *> threadsList;
    for(int i=0; i<NUM_THREADS; i++){
        KnnThread *thread = new KnnThread(elements, index, index+i, QString().setNum(i+1), NUM_THREADS, resultList.at(i), metric);
        threadsList.append(thread);
        thread->start();
    }

    for(int i=0; i<threadsList.size(); i++){
        threadsList.at(i)->wait();
        delete threadsList.at(i);
    }

    metric->clean(elements);
    delete metric;

    for(int k=0; k<resultList.at(0)->size(); k++){
        int success = 0;
        int failure = 0;
        for (int i=0; i<resultList.size(); i++){
            success += resultList.at(i)->at(k).first;
            failure += resultList.at(i)->at(k).second;
        }


        std::cout<<"\nk = "<<k+1<<" Poprawne = "<<success<<", Bledne = "<<failure<<std::endl;
        out<<"\nk = "<<k+1<<" Poprawne = "<<success<<", Bledne = "<<failure<<"\n";
    }

    for (int i = 0; i < resultList.size(); i++) {
        delete resultList.at(i);
    }

    out.flush();
}

void Knn::testSimilarity(QTextStream &out, QList<QSet<QString> > wordSetList, QSet<QString> allWordsSet){
    int index = floor(wordSetList.size()*0.6);

    int NUM_THREADS = QThread::idealThreadCount();

    QList<QList<QPair<int, int> > *> resultList;
    for(int i=0; i<NUM_THREADS; i++){
        resultList.append(new QList<QPair<int, int> >());
    }

    QList<KnnSimilarityThread *> threadsList;
    for(int i=0; i<NUM_THREADS; i++){
        KnnSimilarityThread *thread = new KnnSimilarityThread(wordSetList, allWordsSet, labelsList, index, index+i, *this, QString().setNum(i+1), NUM_THREADS, resultList.at(i));
        threadsList.append(thread);
        thread->start();
    }

    for(int i=0; i<threadsList.size(); i++){
        threadsList.at(i)->wait();
        delete threadsList.at(i);
    }

    for(int k=0; k<resultList.at(0)->size(); k++){
        int success = 0;
        int failure = 0;
        for (int i=0; i<resultList.size(); i++){
            success += resultList.at(i)->at(k).first;
            failure += resultList.at(i)->at(k).second;
        }

        std::cout<<"\nk = "<<k+1<<" Poprawne = "<<success<<", Bledne = "<<failure<<std::endl;
        out<<"\nk = "<<k+1<<" Poprawne = "<<success<<", Bledne = "<<failure<<"\n";
    }

    for (int i = 0; i < resultList.size(); i++) {
        delete resultList.at(i);
    }

    out.flush();
}

double Knn::jaccardSimilarity(QSet<QString> set1, QSet<QString> set2){
    if(set1.size()==0 && set2.size()==0){
        return 1;
    }
    QSet<QString> sumSet = set1+set2;

    return 1.0*set1.intersect(set2).size()/sumSet.size();
}

double Knn::smcSimilarity(QSet<QString> set1, QSet<QString> set2, QSet<QString> allWordsSet){
    QSet<QString> notSet1 = allWordsSet - set1;
    QSet<QString> notSet2 = allWordsSet - set2;

    return 1.0*(set1.intersect(set2).size()+notSet1.intersect(notSet2).size())/allWordsSet.size();
}



