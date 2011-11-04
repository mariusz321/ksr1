#ifndef ELEMENT_H
#define ELEMENT_H

#include <QVector>
#include <QHash>

struct Element {
    union {
        QVector<double> *features;
        QHash<QString, int> *ngrams;
    };
    QVector<double> *ngramSizes;
    qint8 classID;
    QString label;
};

#endif // ELEMENT_H
