#include "ManhattanMetric.h"

#include <cmath>

double ManhattanMetric::distance(const QVector<double> &vect1, const QVector<double> &vect2) const
{
    double sum = 0;
    const int limit = vect1.size();
    const double *v1Data = vect1.constData();
    const double *v2Data = vect2.constData();
    for (int i = 0; i < limit; i++) {
        sum += fabs(v1Data[i] - v2Data[i]);
    }
    return sum;
}
