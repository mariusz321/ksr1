#include "knnthread.h"
#include "MetricInterface.h"
#include "Element.h"

#include <iostream>

KnnThread::KnnThread(const QVector<Element> &elementsVector, int index1, int index2, QString name, int numThreads, QList<QPair<int, int> > *resultList, const MetricInterface *metric) :
    mElementsVector(elementsVector),
    index1(index1),
    index2(index2),
    mMetric(metric),
    name(name),
    numThreads(numThreads)
{
    this->resultList=resultList;
}

void KnnThread::run(){
    QVector<QPair<double, int> > distancePairVector(index1); //first - odleglosc, second - indeks wektora wzgledem ktorego byla mierzona odleglosc

    for(int k=1; k<=100; k++){
        resultList->append(QPair<int, int>(0, 0));
    }

    double distance;

    QFile file(name + ".txt");
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);

        for (int i = index2; i < mElementsVector.size(); i += numThreads) { //wektory niesklasyfikowane
            std::cout<<i<<std::endl;//////
            out<<"\n\nWektor: "<<i<<"\n";//////
            for(int j=0; j<index1; j++){
                distance = mMetric->distance(mElementsVector.at(i), mElementsVector.at(j));
                QPair<double, int> distancePair(distance, j);
                distancePairVector[j]=distancePair;
            }
            qSort(distancePairVector);
            for(int k=1; k<=100; k++){
                QMap<QString, int> labelsToCountMap;
                for(int a=0; a<k && a<distancePairVector.size(); a++){
                    labelsToCountMap[mElementsVector.at(distancePairVector.at(a).second).label]++;
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
                out<<"RealLabel = "<<mElementsVector.at(i).label<<endl;
                out.flush();

                if(resultLabel==mElementsVector.at(i).label){
                    (*resultList)[k-1].first++;
                }else{
                    (*resultList)[k-1].second++;
                }
            }
        }
    }
}
