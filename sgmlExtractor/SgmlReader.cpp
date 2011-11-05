#undef __STRICT_ANSI__
#include "SgmlReader.h"

#include <QDebug>

SgmlReader::SgmlReader(QStringList labelsList, QString tag)
{

    tagRegExp = QRegExp("<"+tag+">");
    tagRegExp2 = QRegExp("<"+tag+">.*(?=</"+tag+">)");
    bodyStartRegExp = QRegExp("<BODY>");
    bodyStartRegExp2 = QRegExp("<BODY>.*");
    bodyEndRegExp = QRegExp(".*(?=</BODY>)");
    this->labelsList = labelsList;
}

QList<QPair<QString, QString> > SgmlReader::readDirectory(QString dirName){
    int allArticlesCount = 0;
    int articlesCount = 0;
    QDir directory(dirName);
    QFileInfoList fileInfoList = directory.entryInfoList();
    QList<QPair<QString, QString> > labelsArticlesPairs;

    foreach (const QFileInfo &fileInfo, fileInfoList) {
        qDebug() << fileInfo.absoluteFilePath();

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
    qDebug() << "Liczba wszystkich artykulow:" << allArticlesCount;
    qDebug() << "Liczba odpowiednich artykulow:" << articlesCount;

    return labelsArticlesPairs;
}
