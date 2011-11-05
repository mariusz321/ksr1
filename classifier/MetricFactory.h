#ifndef METRICFACTORY_H
#define METRICFACTORY_H

#include "MetricInterface.h"

class MetricFactory
{
    MetricFactory() = delete;
public:
    enum Metric { EUCLIDEAN, MANHATTAN, CHEBYSHEV, NORMALIZED, NGRAM};
    static MetricInterface *getNewMetric (Metric metric);//(const QString &name);
};

#endif // METRICFACTORY_H
