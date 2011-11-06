#undef __STRICT_ANSI__
#include <QtCore/QCoreApplication>
#include <QElapsedTimer>
#include <iostream>
#include "knn.h"
#include "knnsimilaritythread.h"
#include "sgmlreader.h"
#include "tfidf.h"
#include "MIKeywordLoader.h"

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString DIRECTORY_NAME = QString("texts");
    bool KNN = false;
    bool EXTRACTION = true;
    bool SIMILARITY = false;
    bool KEYWORDS = true;

    /*QStringList labelsList;
    labelsList.append("WEST-GERMANY");
    labelsList.append("USA");
    labelsList.append("FRANCE");
    labelsList.append("UK");
    labelsList.append("CANADA");
    labelsList.append("JAPAN");

    QString tag = "PLACES";*/

    QStringList labelsList;
    labelsList.append("COFFEE");
    labelsList.append("GOLD");
    labelsList.append("SHIP");
    labelsList.append("SUGAR");

    QString tag = "TOPICS";

//    QStringList labelsList;
//    labelsList.append("CAKE");
//    labelsList.append("PASTA");

//    QString tag = "DISH";

    SgmlReader sgmlReader = SgmlReader(labelsList, tag);
    //sgmlReader.findLabels(DIRECTORY_NAME);


    QElapsedTimer timer;
    timer.start();

    if(SIMILARITY){
        QList<QPair<QString, QString> > labelsArticlesPairs = sgmlReader.readDirectory(DIRECTORY_NAME);
        QMap<QString, int> wordToCountMap = sgmlReader.countWords(labelsArticlesPairs);
        QSet<QString> allWordsSet = sgmlReader.getAllWordsSet(wordToCountMap, 0.0, 0.99);
        QList<QSet<QString> > wordSetList = sgmlReader.getWordSets(labelsArticlesPairs, allWordsSet);
        QFile file("log.txt");
        if(file.open(QIODevice::WriteOnly)){
            QTextStream out(&file);

            Knn knn;
            knn.initLabels(labelsArticlesPairs);
            std::cout<<"Czas wczytywania: "<<timer.elapsed()<<" ms"<<std::endl;
            out<<"Czas wczytywania: "<<timer.elapsed()<<" ms\n";
            knn.testSimilarity(out, wordSetList, allWordsSet);

            //czas obliczen
            std::cout<<"Czas obliczen: "<<timer.elapsed()<<std::endl;
            out<<endl<<"Czas obliczen: "<<timer.elapsed()<<" ms\n";

            file.close();
        }

    }

    if(EXTRACTION){
        QList<QPair<QString, QString> > labelsArticlesPairs = sgmlReader.readDirectory(DIRECTORY_NAME);
        /*for (int i = 0; i < labelsArticlesPairs.size(); i++) {
            qDebug() << "article:" << labelsArticlesPairs.at(i).second;
        }*/
        QMap<QString, int> wordToCountMap;
        if (KEYWORDS) {
            KeywordLoaderInterface *kli = new MIKeywordLoader();
            QList<QPair<QString, QStringList> > keywords = kli->loadFromFile("keywords.txt");
            QSet<QString> keywordsSet;
            for (int i = 0; i < keywords.size(); i++) {
                for (int j = 0; j < keywords.at(i).second.size(); j++) {
                    keywordsSet.insert(keywords.at(i).second.at(j));
                }
            }
            for (int i = 0; i < keywordsSet.size(); i++) {
                const QString word = keywordsSet.values().at(i);
                QRegExp re(QString("\\b(%1)\\b").arg(word), Qt::CaseInsensitive);
                //qDebug() << "trying" << re.pattern();
                for (int j = 0; j < labelsArticlesPairs.size(); j++) {
                    if (re.indexIn(labelsArticlesPairs.at(j).second)) {
                        //qDebug() << "found";
                        wordToCountMap[word] += re.capturedTexts().size();
                    }
                }
            }
        } else {
            wordToCountMap = sgmlReader.countWords(labelsArticlesPairs);
        }
        QList<QPair<int, QString> > wordsCountList = sgmlReader.getWordsCountList(wordToCountMap, 0.9, 0.099);
        QList<QRegExp> regexpList = sgmlReader.getQRegExpList(wordsCountList);

        //TFIDF
        Tfidf tfidf;

        QList<QList<double> > tfList = tfidf.computeTfList(labelsArticlesPairs, wordsCountList, regexpList);//lista wspolczynnikow tf dla artykulow
        QVector<double> idfVector = tfidf.computeIDF(sgmlReader.articlesCount, tfidf.wordInArticles);
        QList<QList<double> > tfidfList = tfidf.computeTFIDF(tfList, idfVector);

        tfidf.saveToFile(tfidfList, labelsArticlesPairs, "wektory.txt");
    }

    if(KNN){
        QFile file("log.txt");
        if(file.open(QIODevice::WriteOnly)){
            QTextStream out(&file);

            Knn knn;
            std::cout<<"Czas wczytywania: "<<timer.elapsed()<<" ms"<<std::endl;
            out<<"Czas wczytywania: "<<timer.elapsed()<<" ms\n";
            knn.testDistance(out);

            //czas obliczen
            std::cout<<"Czas obliczen: "<<timer.elapsed()<<std::endl;
            out<<endl<<"Czas obliczen: "<<timer.elapsed()<<" ms\n";

            file.close();
        }
    }
    return 0;//a.exec();
}
