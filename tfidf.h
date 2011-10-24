#ifndef TFIDF_H
#define TFIDF_H

#include <QVector>
#include <QRegExp>
#include <QPair>
#include <QFile>
#include <QTextStream>

class Tfidf
{
public:
    Tfidf();

    QVector<int> wordInArticles; //liczba artykulow, w ktorych wystepuje slowo
    int countMatches(QRegExp, QString);
    QList<double> computeTF(QVector<int>);
    QList<QList<double> > computeTfList(QList<QPair<QString, QString> >, QList<QPair<int, QString> >, QList<QRegExp>);
    QVector<double> computeIDF(int, QVector<int>);
    QList<QList<double> > computeTFIDF(QList<QList<double> >, QVector<double>);
    void saveToFile(QList<QList<double> >, QList<QPair<QString, QString> >, QString);
};

#endif // TFIDF_H
