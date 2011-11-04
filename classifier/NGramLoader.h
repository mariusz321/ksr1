#ifndef NGRAMLOADER_H
#define NGRAMLOADER_H

#include "Element.h"

#include <QVector>

class NGramLoader
{
public:
    static QVector<Element> loadData(const QStringList &arguments);
    static void clean(const QVector<Element> &elements);
};

#endif // NGRAMLOADER_H
