#ifndef VECTORLOADER_H
#define VECTORLOADER_H

#include "Element.h"

#include <QVector>

class VectorLoader
{
public:
    static QVector<Element> loadData(const QStringList &arguments, const bool &normalize);
    static void clean(const QVector<Element> &elements);
};

#endif // VECTORLOADER_H
