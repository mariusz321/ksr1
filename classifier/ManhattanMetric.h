#ifndef MANHATTANMETRIC_H
#define MANHATTANMETRIC_H

#include "MetricInterface.h"

class ManhattanMetric : public MetricInterface
{
public:
    QVector<Element> loadData(const QStringList &arguments) const;
    double distance(const Element &e1, const Element &e2) const;
    void clean(const QVector<Element> &elements) const;
};

#endif // MANHATTANMETRIC_H
