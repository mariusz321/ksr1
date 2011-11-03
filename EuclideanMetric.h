#ifndef EUCLIDEANMETRIC_H
#define EUCLIDEANMETRIC_H

#include "MetricInterface.h"

class EuclideanMetric : public MetricInterface
{
public:
    double distance(const QVector<double> &vect1, const QVector<double> &vect2) const;
};

#endif // EUCLIDEANMETRIC_H
