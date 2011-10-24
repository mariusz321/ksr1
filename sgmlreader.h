#ifndef SGMLREADER_H
#define SGMLREADER_H

#include <QFile>
#include <QDir>
#include <QPair>
#include <QMap>
#include <QTextStream>

class SgmlReader
{
private:
    QRegExp tagRegExp;
    QRegExp tagRegExp2;
    QRegExp bodyStartRegExp;
    QRegExp bodyStartRegExp2;
    QRegExp bodyEndRegExp;
    QStringList labelsList;
public:
    int articlesCount;
    int allArticlesCount;
    QList<QPair<QString, QString> > labelsArticlesPairs;

    SgmlReader(QStringList, QString);
    QList<QPair<QString, QString> > readDirectory(QString);
    QMap<QString, int> countWords(QList<QPair<QString, QString> >);
    QList<QPair<int, QString> > getWordsCountList(QMap<QString, int>, float, float);
    QList<QRegExp> getQRegExpList(QList<QPair<int, QString> >);

    void findLabels(QString);
};

#endif // SGMLREADER_H
