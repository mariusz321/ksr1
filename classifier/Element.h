#ifndef ELEMENT_H
#define ELEMENT_H

#include <QVector>
#include <QSet>

struct Element {
    union {
        QVector<double> *features;
        QSet<QString> *ngrams;
    };
    qint8 classID;
    QString label;
};

#endif // ELEMENT_H
