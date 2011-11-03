#include "MetricFactory.h"
#include "EuclideanMetric.h"

#include <QString>

MetricInterface *MetricFactory::getNewMetric(const QString &name)
{
    if (name == "euclidean") {
        return new EuclideanMetric();
    } else {
        return nullptr;
    }
}
