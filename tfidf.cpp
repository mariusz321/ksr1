#include "tfidf.h"
#include <cmath>

Tfidf::Tfidf()
{
}

int Tfidf::countMatches(QRegExp regexp, QString text){
    int count = 0;
    int pos = 0;
    while ((pos = regexp.indexIn(text, pos)) != -1) {
        count++;
        pos += regexp.matchedLength();
    }
    return count;
}

QList<double> Tfidf::computeTF(QVector<int> counts){
    int sum=0;
    QList<double> list = QList<double>();
    foreach(int count, counts){
        sum+=count;
    }
    if(sum==0){
        for(int i=0; i<counts.size(); i++){
            list.append(0);
        }
    } else{
        for(int i=0; i<counts.size(); i++){
            list.append(1.0*counts.at(i)/sum);
        }
    }

    return list;
}
QList<QList<double> > Tfidf::computeTfList(QList<QPair<QString, QString> > labelsArticlesPairs, QList<QPair<int, QString> > wordsCountList, QList<QRegExp> regexpList){
        QList<QList<double> > tfList = QList<QList<double> >(); //lista wspolczynnikow tf dla artykulu
        wordInArticles = QVector<int>(wordsCountList.size()); //liczba dokumentow zawierajacych przynajmniej jedno wystapienie danej etykiety
        QPair<QString, QString> pair;

            foreach(pair, labelsArticlesPairs){
                QString article = pair.second;
                QVector<int> counts = QVector<int>(wordsCountList.size()); //liczby wystapien poszczegolnych etykiet w artykule
                for(int i=0; i<wordsCountList.size(); i++){
                    counts[i] = countMatches(regexpList.at(i), article);
                    if (counts[i] > 0){
                        wordInArticles[i]++;
                    }
                }
                QList<double> tf = computeTF(counts);
                tfList.append(tf);
    //            for(int j=0; j<wordsCountList.size(); j++) {
    //                std::cout<<wordsCountList.at(j).second.toAscii().data()<<" : "<<tfList.at(j)<<std::endl;
    //            }

        }
            return tfList;
}

QVector<double> Tfidf::computeIDF(int articlesCount, QVector<int> labelInArticles){
    QVector<double> idf = QVector<double>(labelInArticles.size());
    for(int i=0; i<labelInArticles.size(); i++){
        if(labelInArticles.at(i)==0){
            idf[i]=0;
        }else{
            idf[i]=log(1.0*articlesCount/labelInArticles.at(i));
            //std::cout<<idf[i]<<std::endl;
        }
    }

    return idf;
}

QList<QList<double> > Tfidf::computeTFIDF(QList<QList<double> > tf, QVector<double> idf){
    QList<QList<double> > tfidfList = QList<QList<double> >();
    foreach(QList<double> list, tf){
        QList<double> tfidf = QList<double>();
        for(int i=0; i<list.size(); i++){
            tfidf.append(list[i]*idf.at(i));
        }
        tfidfList.append(tfidf);
    }
    return tfidfList;
}

void Tfidf::saveToFile(QList<QList<double> > tfidfList, QList<QPair<QString, QString> > labelsArticlesPairs, QString fileName){
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        for(int i=0; i<tfidfList.size(); i++){
            QList<double> list = tfidfList.at(i);
            out<<labelsArticlesPairs.at(i).first<<endl; //zapisanie etykiety
            out<<"[";
            for (int j=0; j<list.size(); j++){ //zapisanie wektora
                double tfidf = list.at(j);
                if(j==0){
                    out<<tfidf;
                }else{
                    out<<";"<<tfidf;
                }
            }
            out<<"]"<<endl;
        }
    }
    file.close();
}
