#undef __STRICT_ANSI__
#include "knnsimilaritythread.h"
#include <iostream>

KnnSimilarityThread::KnnSimilarityThread(QList<QSet<QString> > wordSetList, QSet<QString> allWordsSet, QList<QString> labelsList,  int index1, int index2, Knn knn, QString name, int numThreads, QList<QPair<int, int> > *resultList)
{
    this->wordSetList=wordSetList;
    this->allWordsSet=allWordsSet;
    this->labelsList=labelsList;
    this->index1=index1;
    this->index2=index2;
    this->knn=knn;
    this->resultList=resultList;
    this->numThreads=numThreads;
    this->name=name;
}

void KnnSimilarityThread::run(){

    enum{JACCARD, NGRAM, NEW};
    const int type= NEW;

    QVector<QPair<double, int> > similarityPairVector(index1); //first - podobienstwo, second - indeks wektora wzgledem ktorego byla mierzona odleglosc

    for(int k=1; k<=100; k++){
        resultList->append(QPair<int, int>(0, 0));
    }

    double similarity;

    QFile file(name.append(".txt"));
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////
        QList<QSet<QString> > ngramSetList = QList<QSet<QString> >();
        if(type==NEW){

#define SIZE 4

            for(int i=0; i<index1; i++){
                QSet<QString> newSet = QSet<QString>();
                foreach(QString string, wordSetList.at(i)){
                    if (string.size()<=SIZE){
                        newSet.insert(string);
                    }
                    else{
                        for (int k=0; k<string.size()-SIZE+1; k++){
                            newSet.insert(string.midRef(k, SIZE).toString());
                        }
                    }
                }
                ngramSetList.append(newSet);
            }
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////

        for(int i=index2; i<wordSetList.size(); i+=numThreads){ //zbiory niesklasyfikowane
            std::cout<<i<<std::endl;//////
            out<<"\n\nWektor: "<<i<<"\n";//////
            for(int j=0; j<index1; j++){
                if(type==JACCARD){
                    similarity = knn.jaccardSimilarity(wordSetList.at(i), wordSetList.at(j));
                }
                if(type==NGRAM){
                similarity = knn.ngramSimilarity(wordSetList.at(i), wordSetList.at(j));
                }
                ////////////////////////////////////////////////////////////////////////////
                if(type==NEW){
                    QSet<QString> newSet = QSet<QString>();
                    foreach(QString string, wordSetList.at(i)){
                        if (string.size()<=SIZE){
                            newSet.insert(string);
                        }
                        else{
                            for (int k=0; k<string.size()-SIZE+1; k++){
                                newSet.insert(string.midRef(k, SIZE).toString());
                            }
                        }
                    }

                ////////////////////////////////////////////////////////////////////////////

                similarity = knn.newSimilarity(wordSetList.at(i), wordSetList.at(j), newSet, ngramSetList.at(j));
                }
                QPair<double, int> similarityPair(similarity, j);
                similarityPairVector[j]=similarityPair;
            }
            qSort(similarityPairVector.begin(),similarityPairVector.end(),qGreater<QPair<double, int> >());
            for(int k=1; k<=100; k++){
                QMap<QString, int> labelsToCountMap;
                for(int a=0; a<k && a<similarityPairVector.size(); a++){
                    labelsToCountMap[labelsList.at(similarityPairVector.at(a).second)]++;
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
