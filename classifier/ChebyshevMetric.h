#ifndef CHEBYSHEVMETRIC_H
#define CHEBYSHEVMETRIC_H

#include "MetricInterface.h"

class ChebyshevMetric : public MetricInterface
{
public:
    QVector<Element> loadData(const QStringList &arguments, const bool &normalize) const;
    double distance(const Element &e1, const Element &e2) const;
    void clean(const QVector<Element> &elements) const;
};

#endif // CHEBYSHEVMETRIC_H
