#ifndef METRICFACTORY_H
#define METRICFACTORY_H

#include "MetricInterface.h"

class MetricFactory
{
    MetricFactory() = delete;
public:
    static MetricInterface *getNewMetric(const QString &name);
};

#endif // METRICFACTORY_H
