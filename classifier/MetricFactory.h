#ifndef METRICFACTORY_H
#define METRICFACTORY_H

#include "MetricInterface.h"

class MetricFactory
{
    MetricFactory() = delete;
public:
    static MetricInterface *getNewMetric (int en);//(const QString &name);
    enum { EUCLIDEAN, MANHATTAN, CHEBYSHEV, NORMALIZED, NGRAM};
};

#endif // METRICFACTORY_H
