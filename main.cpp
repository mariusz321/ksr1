#include <QtCore/QCoreApplication>
#include <QElapsedTimer>
#include <iostream>
#include "knn.h"
#include "knnsimilaritythread.h"
#include "sgmlreader.h"
#include "tfidf.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString DIRECTORY_NAME = QString("texts");
    bool KNN = false;
    bool EXTRACTION = false;
    bool SIMILARITY = true;

//        QStringList labelsList = QStringList();
//        labelsList.append("WEST-GERMANY");
//        labelsList.append("USA");
//        labelsList.append("FRANCE");
//        labelsList.append("UK");
//        labelsList.append("CANADA");
//        labelsList.append("JAPAN");

//        QString tag = "PLACES";

    QStringList labelsList = QStringList();
    labelsList.append("COFFEE");
    labelsList.append("GOLD");
    labelsList.append("SHIP");
    labelsList.append("SUGAR");

    QString tag = "TOPICS";

    SgmlReader sgmlReader = SgmlReader(labelsList, tag);
    //reader.findLabels(DIRECTORY_NAME);


    QElapsedTimer timer = QElapsedTimer();
    timer.start();

    if(SIMILARITY){
        QList<QPair<QString, QString> > labelsArticlesPairs = sgmlReader.readDirectory(DIRECTORY_NAME);
        QMap<QString, int> wordToCountMap = sgmlReader.countWords(labelsArticlesPairs);
        QSet<QString> allWordsSet = sgmlReader.getAllWordsSet(wordToCountMap, 0.0, 0.99);
        QList<QSet<QString> > wordSetList = sgmlReader.getWordSets(labelsArticlesPairs, allWordsSet);
        QFile file("log.txt");
        if(file.open(QIODevice::WriteOnly)){
            QTextStream out(&file);

            Knn knn = Knn();
            knn.initLabels(labelsArticlesPairs);
            std::cout<<"Czas wczytywania: "<<timer.elapsed()<<" ms"<<std::endl;
            out<<"Czas wczytywania: "<<timer.elapsed()<<" ms\n";
            knn.testSimilarity(out, wordSetList, allWordsSet);

            //czas obliczen
            out<<endl<<"Czas obliczen: "<<timer.elapsed()<<" ms\n";

            file.close();
        }

    }

    if(EXTRACTION){
        QList<QPair<QString, QString> > labelsArticlesPairs = sgmlReader.readDirectory(DIRECTORY_NAME);
        QMap<QString, int> wordToCountMap = sgmlReader.countWords(labelsArticlesPairs);
        QList<QPair<int, QString> > wordsCountList = sgmlReader.getWordsCountList(wordToCountMap, 0.9, 0.099);
        QList<QRegExp> regexpList = sgmlReader.getQRegExpList(wordsCountList);

        //TFIDF
        Tfidf tfidf = Tfidf();

        QList<QList<double> > tfList = tfidf.computeTfList(labelsArticlesPairs, wordsCountList, regexpList);//lista wspolczynnikow tf dla artykulow
        QVector<double> idfVector = tfidf.computeIDF(sgmlReader.articlesCount, tfidf.wordInArticles);
        QList<QList<double> > tfidfList = tfidf.computeTFIDF(tfList, idfVector);

        tfidf.saveToFile(tfidfList, labelsArticlesPairs, "wektory.txt");
    }

    if(KNN){
        QFile file("log.txt");
        if(file.open(QIODevice::WriteOnly)){
            QTextStream out(&file);

            Knn knn = Knn();
            knn.readVetors("wektory.txt");
            std::cout<<"Czas wczytywania: "<<timer.elapsed()<<" ms"<<std::endl;
            out<<"Czas wczytywania: "<<timer.elapsed()<<" ms\n";
            knn.testDistance(out);

            //czas obliczen
            out<<endl<<"Czas obliczen: "<<timer.elapsed()<<" ms\n";

            file.close();
        }
    }
    return 0;//a.exec();
}
