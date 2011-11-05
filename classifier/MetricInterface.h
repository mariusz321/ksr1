#ifndef METRICINTERFACE_H
#define METRICINTERFACE_H

#include "Element.h"

#include <QVector>

class MetricInterface {
public:
    virtual ~MetricInterface();
    virtual QVector<Element> loadData(const QStringList &arguments, const bool &normalize) const = 0;
    virtual double distance(const Element &e1, const Element &e2) const = 0;
    virtual void clean(const QVector<Element> &elements) const = 0;
};

#endif // METRICINTERFACE_H
