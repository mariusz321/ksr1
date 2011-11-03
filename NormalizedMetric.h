#ifndef NORMALIZEDMETRIC_H
#define NORMALIZEDMETRIC_H

#include "MetricInterface.h"

class NormalizedMetric : public MetricInterface
{
public:
    double distance(const QVector<double> &vect1, const QVector<double> &vect2) const;
};

#endif // NORMALIZEDMETRIC_H
