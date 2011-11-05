#ifndef NORMALIZEDMETRIC_H
#define NORMALIZEDMETRIC_H

#include "MetricInterface.h"

class NormalizedMetric : public MetricInterface
{
public:
    QVector<Element> loadData(const QStringList &arguments, const bool &normalize) const;
    double distance(const Element &e1, const Element &e2) const;
    void clean(const QVector<Element> &elements) const;
};

#endif // NORMALIZEDMETRIC_H
