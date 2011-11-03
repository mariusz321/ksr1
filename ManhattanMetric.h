#ifndef MANHATTANMETRIC_H
#define MANHATTANMETRIC_H

#include "MetricInterface.h"

class ManhattanMetric : public MetricInterface
{
public:
    double distance(const QVector<double> &vect1, const QVector<double> &vect2) const;
};

#endif // MANHATTANMETRIC_H
