#include "NormalizedMetric.h"

#include <cmath>

double NormalizedMetric::distance(const QVector<double> &vect1, const QVector<double> &vect2) const
{
    double length1 = 0;
    double length2 = 0;
    const int limit = vect1.size();
    const double *v1Data = vect1.constData();
    const double *v2Data = vect2.constData();
    for (int i = 0; i < limit; i++) {
        length1 += v1Data[i] * v1Data[i];
        length2 += v2Data[i] * v2Data[i];
    }
    length1 = sqrt(length1);
    length2 = sqrt(length2);

    double sum = 0;
    for (int i = 0; i < limit; i++) {
        double temp = v1Data[i] / length1 - v2Data[i] / length2;
        sum += temp * temp;
    }
    return sqrt(sum);
}
