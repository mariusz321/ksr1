#ifndef EUCLIDEANMETRIC_H
#define EUCLIDEANMETRIC_H

#include "MetricInterface.h"

class EuclideanMetric : public MetricInterface
{
public:
    QVector<Element> loadData(const QStringList &arguments) const;
    double distance(const Element &e1, const Element &e2) const;
    void clean(const QVector<Element> &elements) const;
};

#endif // EUCLIDEANMETRIC_H
