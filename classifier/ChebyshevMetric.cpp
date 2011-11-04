#include "ChebyshevMetric.h"
#include "VectorLoader.h"

#include <cmath>

double ChebyshevMetric::distance(const Element &e1, const Element &e2) const
{
    double max = 0;
    const int limit = e1.features->size();
    const double *v1Data = e1.features->constData();
    const double *v2Data = e2.features->constData();
    for (int i = 0; i < limit; i++) {
        double temp = fabs(v1Data[i] - v2Data[i]);
        if (temp > max) {
            max = temp;
        }
    }
    return max;
}

QVector<Element> ChebyshevMetric::loadData(const QStringList &arguments) const
{
    return VectorLoader::loadData(arguments);
}

void ChebyshevMetric::clean(const QVector<Element> &elements) const
{
    VectorLoader::clean(elements);
}
