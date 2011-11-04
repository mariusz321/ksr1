#include "NormalizedMetric.h"
#include "VectorLoader.h"

#include <cmath>

double NormalizedMetric::distance(const Element &e1, const Element &e2) const
{
    double length1 = 0;
    double length2 = 0;
    const int limit = e1.features->size();
    const double *v1Data = e1.features->constData();
    const double *v2Data = e2.features->constData();
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

QVector<Element> NormalizedMetric::loadData(const QStringList &arguments) const
{
    return VectorLoader::loadData(arguments);
}

void NormalizedMetric::clean(const QVector<Element> &elements) const
{
    VectorLoader::clean(elements);
}
