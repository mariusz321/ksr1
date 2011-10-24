#include "sgmlreader.h"
#include <iostream>
#include <cmath>

SgmlReader::SgmlReader(QStringList labelsList, QString tag)
{
    allArticlesCount=0;
    articlesCount=0;

    tagRegExp = QRegExp("<"+tag+">");
    tagRegExp2 = QRegExp("<"+tag+">.*(?=</"+tag+">)");
    bodyStartRegExp = QRegExp("<BODY>");
    bodyStartRegExp2 = QRegExp("<BODY>.*");
    bodyEndRegExp = QRegExp(".*(?=</BODY>)");
    this->labelsList = labelsList;
}
void SgmlReader::findLabels(QString dirName){
    QDir directory = QDir(dirName);
    QFileInfoList fileInfoList = directory.entryInfoList();

    int articles=0;

    QMap<QString, int> map = QMap<QString, int>();
    foreach (QFileInfo fileInfo, fileInfoList) {
        std::cout<<fileInfo.absoluteFilePath().toAscii().data()<<std::endl;

        QFile file(fileInfo.absoluteFilePath());
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            QTextStream in(&file);

            while (!in.atEnd()) {
                QString line = in.readLine();
                if(line.contains(tagRegExp)){
                    tagRegExp2.indexIn(line);
                    QString topic = tagRegExp2.cap();
                    topic.remove(tagRegExp);
                    topic.toUpper();
                    if(!topic.isEmpty() &&!topic.contains("</D><D>")){
                        topic.remove(QRegExp("</D>|<D>"));
                        if(labelsList.contains(topic, Qt::CaseInsensitive)){
                            map[topic]++;
                            articles++;
                        }
                    }
                }
            }
        }
    }
    QFile file("labels.txt");
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);

        QMapIterator<QString, int> it(map);
        while(it.hasNext()){
            it.next();
            std::cout<<it.key().toAscii().data()<<": "<<it.value()<<std::endl;
            out<<it.key().toAscii().data()<<": "<<it.value()<<endl;
        }
        std::cout<<"labels = "<<map.size()<<std::endl;
        std::cout<<"articles = "<<articles<<std::endl;
        out<<"labels = "<<map.size()<<endl;
        out<<"articles = "<<articles<<endl;
    }
}

QList<QPair<QString, QString> > SgmlReader::readDirectory(QString dirName){
    QDir directory = QDir(dirName);
    QFileInfoList fileInfoList = directory.entryInfoList();
    labelsArticlesPairs = QList<QPair<QString, QString> >();

    foreach (QFileInfo fileInfo, fileInfoList) {
        std::cout<<fileInfo.absoluteFilePath().toAscii().data()<<std::endl;

        QFile file(fileInfo.absoluteFilePath());
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);

        bool searchBodyStart = false;
        bool searchBodyEnd = false;

        QPair<QString, QString> pair;
        QString article;
        while (!in.atEnd()) {
            QString line = in.readLine();

            if(!searchBodyStart && !searchBodyEnd && line.contains(tagRegExp)){
                tagRegExp2.indexIn(line);
                QString place = tagRegExp2.cap();
                place.remove(tagRegExp);
                place = place.mid(3, place.size()-7);
                allArticlesCount++;

                if(labelsList.contains(place.toUpper())){
                    pair = QPair<QString, QString>();
                    pair.first = place.toUpper();
                    articlesCount++;
                    searchBodyStart = true;
                }
            } else if(searchBodyStart){
                if(line.contains(bodyStartRegExp)){
                    bodyStartRegExp2.indexIn(line);
                    QString bodyLine = bodyStartRegExp2.cap();
                    bodyLine.remove(bodyStartRegExp);
                    article = bodyLine;
                    searchBodyStart = false;
                    searchBodyEnd = true;
                }
            } else if(searchBodyEnd){
                if(!line.contains(bodyEndRegExp)){
                    article.append(" "+line);
                } else{
                    bodyEndRegExp.indexIn(line);
                    article.append(" "+bodyEndRegExp.cap());
                    searchBodyEnd = false;
                    article.remove(QRegExp("[.,]|&[^;]+;"));
                    article = article.toUpper();
                    pair.second = article;
                    labelsArticlesPairs.append(pair);
                    //std::cout<<article.toAscii().data()<<std::endl; //wyswietlenie artykulu
                }
            }
        }
    }
    std::cout<<"Liczba wszystkich artykulow: "<<allArticlesCount<<std::endl;
    std::cout<<"Liczba odpowiednich artykulow: "<<articlesCount<<std::endl;

    return labelsArticlesPairs;
}


QMap<QString, int> SgmlReader::countWords(QList<QPair<QString, QString> > labelsArticlesPairs){
    QMap<QString, int> wordToCountMap = QMap<QString, int>(); //mapa slowo-liczba_wystapien
    QRegExp wordRegExp = QRegExp("\\b[a-z]+(-[a-z]+)*\\b", Qt::CaseInsensitive);
    QPair<QString, QString> pair;
    foreach(pair, labelsArticlesPairs){
        int pos = 0;
        while ((pos = wordRegExp.indexIn(pair.second, pos)) != -1) {
            pos += wordRegExp.matchedLength();
            QString word = wordRegExp.cap();
            wordToCountMap[word]++;
        }
    }
    return wordToCountMap;
}



QList<QPair<int, QString> > SgmlReader::getWordsCountList(QMap<QString, int> wordToCountMap, float listCutStart=-1, float listCutLen=-1){
    QList<QPair<int, QString> > wordsCountList = QList<QPair<int, QString> >(); //lista par liczba_wystapien-slowo
    QMapIterator<QString, int> i = QMapIterator<QString, int>(wordToCountMap);
    while(i.hasNext()){
        i.next();
        wordsCountList.append(QPair<int, QString>(i.value(), i.key()));
    }
    qSort(wordsCountList);
    if(listCutStart >=0 && listCutLen >0){
        int listSize = wordsCountList.size();
        wordsCountList = wordsCountList.mid(floor(listSize*listCutStart), ceil(listSize*listCutLen));
    }

    // zapis listy do pliku
    QFile file("mapa.txt");
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        QPair<int, QString> countWordPair;
        foreach(countWordPair, wordsCountList){
            out<<countWordPair.second<<"\t"<<countWordPair.first<<endl;
        }
        file.close();
    }
    return wordsCountList;
}


QList<QRegExp> SgmlReader::getQRegExpList(QList<QPair<int, QString> > pairList){
    QList<QRegExp> regexpList = QList<QRegExp>();
    QPair<int, QString> pair;
    foreach(pair, pairList){
        regexpList.append(QRegExp("\\b"+pair.second+"\\b", Qt::CaseInsensitive));
    }
    return regexpList;
}


