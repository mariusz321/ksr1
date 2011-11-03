#ifndef CHEBYSHEVMETRIC_H
#define CHEBYSHEVMETRIC_H

#include "MetricInterface.h"

class ChebyshevMetric : public MetricInterface
{
public:
    double distance(const QVector<double> &vect1, const QVector<double> &vect2) const;
};

#endif // CHEBYSHEVMETRIC_H
