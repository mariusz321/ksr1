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

void Knn::readVetors(QString fileName){
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    vectorsList = QList<QVector<double> >();
    labelsList =  QList<QString>();

    while (!in.atEnd()) {
        QString line = in.readLine();
        labelsList.append(line);

        line = in.readLine();
        line.remove(QRegExp("\\[|\\]"));
        QStringList stringList = line.split(";");
        QVector<double> vect = QVector<double>(stringList.size());
        for(int i =0; i<stringList.size(); i++){
            vect[i] = stringList.at(i).toDouble();
        }
        vectorsList.append(vect);
    }
}

void Knn::initLabels(QList<QPair<QString, QString> > labelsArticlesPairs){
    labelsList =  QList<QString>();
    QPair<QString, QString> labelArticlePair;
    foreach(labelArticlePair, labelsArticlesPairs){
        labelsList.append(labelArticlePair.first);
    }

}

void Knn::testDistance(QTextStream &out){
    int index = floor(vectorsList.size()*0.6);

    int NUM_THREADS = QThread::idealThreadCount();

    QList<QList<QPair<int, int> > *> resultList = QList<QList<QPair<int, int> > *>();
    for(int i=0; i<NUM_THREADS; i++){
        resultList.append(new QList<QPair<int, int> >());
    }

    QList<KnnThread *> threadsList = QList<KnnThread *>();
    QList<MetricInterface *> metricsList;
    for(int i=0; i<NUM_THREADS; i++){
        MetricInterface *metric = MetricFactory::getNewMetric("euclidean");
        metricsList.append(metric);
        KnnThread *thread = new KnnThread(vectorsList, labelsList, index, index+i, QString().setNum(i+1), NUM_THREADS, resultList.at(i), metric);
        threadsList.append(thread);
        thread->start();
    }

    for(int i=0; i<threadsList.size(); i++){
        threadsList.at(i)->wait();
        delete threadsList.at(i);
        delete metricsList.at(i);
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

void Knn::testSimilarity(QTextStream &out, QList<QSet<QString> > wordSetList, QSet<QString> allWordsSet){
    int index = floor(wordSetList.size()*0.6);

    int NUM_THREADS = 4;

    QList<QList<QPair<int, int> > *> resultList = QList<QList<QPair<int, int> > *>();
    for(int i=0; i<NUM_THREADS; i++){
        resultList.append(new QList<QPair<int, int> >());
    }

    QList<KnnSimilarityThread *> threadsList = QList<KnnSimilarityThread *>();
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



