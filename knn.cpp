#include "knn.h"
#include <cmath>
#include <iostream>
#include "knnthread.h"

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

double Knn::euclideanDistance(const QVector<double> &vect1, const QVector<double> &vect2) const {
    double sum = 0;
    double temp;
    for(int i = 0; i<vect1.size(); i++ ){
        temp = vect1.at(i)-vect2.at(i);
        sum += temp*temp;
    }
    return sqrt(sum);
}

double Knn::manhattanDistance(const QVector<double> &vect1, const QVector<double> &vect2) const {
    double sum = 0;
    for(int i = 0; i<vect1.size(); i++ ){
        sum += abs(vect1.at(i)-vect2.at(i));
    }
    return sum;
}

double Knn::chebyshevDistance(const QVector<double> &vect1, const QVector<double> &vect2) const {
    double max = 0;
    double temp;
    for(int i = 0; i<vect1.size(); i++ ){
        temp = abs(vect1.at(i)-vect2.at(i));
        if(temp>max){
            max=temp;
        }
    }
    return max;
}

double Knn::normalizedDistance(const QVector<double> &vect1, const QVector<double> &vect2) const {
    double length1 = 0, length2=0;
    for(int i=0; i<vect1.size(); i++){
        length1+=vect1.at(i)*vect1.at(i);
        length2+=vect2.at(i)*vect2.at(i);
    }
    length1=sqrt(length1);
    length2=sqrt(length2);

    double sum = 0;
    double temp;
    for(int i = 0; i<vect1.size(); i++ ){
        temp = vect1.at(i)/length1-vect2.at(i)/length2;
        sum += temp*temp;
    }
    return sqrt(sum);
}

void Knn::test(QTextStream &out){
    int index = floor(vectorsList.size()*0.6);

    int NUM_THREADS = QThread::idealThreadCount();

    QList<QList<QPair<int, int> > *> resultList = QList<QList<QPair<int, int> > *>();
    for(int i=0; i<NUM_THREADS; i++){
        resultList.append(new QList<QPair<int, int> >());
    }

    QList<KnnThread *> threadsList = QList<KnnThread *>();
    for(int i=0; i<NUM_THREADS; i++){
        KnnThread *thread = new KnnThread(vectorsList, labelsList, index, index+i, *this, QString().setNum(i+1), NUM_THREADS, resultList.at(i));
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
    out.flush();

}


