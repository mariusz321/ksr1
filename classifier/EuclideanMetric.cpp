#include "EuclideanMetric.h"
#include "VectorLoader.h"

#include <cmath>

double EuclideanMetric::distance(const Element &e1, const Element &e2) const
{
    double sum = 0;
    const int limit = e1.features->size();
    const double *v1Data = e1.features->constData();
    const double *v2Data = e2.features->constData();
    for (int i = 0; i < limit; i++) {
        double temp = v1Data[i] - v2Data[i];
        sum += temp * temp;
    }
    return sqrt(sum);
}

QVector<Element> EuclideanMetric::loadData(const QStringList &arguments) const
{
    return VectorLoader::loadData(arguments);
}

void EuclideanMetric::clean(const QVector<Element> &elements) const
{
    VectorLoader::clean(elements);
}
