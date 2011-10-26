#include "knnthread.h"
#include <iostream>

KnnThread::KnnThread(QList<QVector<double> > vectorList, QList<QString> labelsList,  int index1, int index2, Knn knn, QString name, int numThreads, QList<QPair<int, int> > *resultList)
{
    this->vectorList=vectorList;
    this->labelsList=labelsList;
    this->index1=index1;
    this->index2=index2;
    this->knn=knn;
    this->resultList=resultList;
    this->numThreads=numThreads;
    this->name=name;
}

void KnnThread::run(){
    QVector<QPair<double, int> > distancePairVector(index1); //first - odleglosc, second - indeks wektora wzgledem ktorego byla mierzona odleglosc

    for(int k=1; k<=100; k++){
        resultList->append(QPair<int, int>(0, 0));
    }

    double distance;

    QFile file(name.append(".txt"));
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);

        for(int i=index2; i<vectorList.size(); i+=numThreads){ //wektory niesklasyfikowane
            std::cout<<i<<std::endl;//////
            out<<"\n\nWektor: "<<i<<"\n";//////
            for(int j=0; j<index1; j++){
                distance = knn.normalizedDistance(vectorList.at(i), vectorList.at(j));
                QPair<double, int> distancePair(distance, j);
                distancePairVector[j]=distancePair;
            }
            qSort(distancePairVector);
            for(int k=1; k<=100; k++){
                QMap<QString, int> labelsToCountMap;
                for(int a=0; a<k && a<distancePairVector.size(); a++){
                    labelsToCountMap[labelsList.at(distancePairVector.at(a).second)]++;
                }
                QString resultLabel;
                int largestCount = -1;

                QMapIterator<QString, int> iter(labelsToCountMap);
                while (iter.hasNext()) {
                    iter.next();
                    if (iter.value() > largestCount) {
                        resultLabel = iter.key();
                        largestCount = iter.value();
                    }
                }
                out<<endl<<"k = "<<k<<endl;
                out<<"ResultLabel = "<<resultLabel<<endl;
                out<<"RealLabel = "<<labelsList.at(i)<<endl;
                out.flush();

                if(resultLabel==labelsList.at(i)){
                    (*resultList)[k-1].first++;
                }else{
                    (*resultList)[k-1].second++;
                }
            }
        }
    }
}
