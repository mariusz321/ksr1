#include "MetricFactory.h"
#include "EuclideanMetric.h"
#include "ManhattanMetric.h"

#include <QString>

MetricInterface *MetricFactory::getNewMetric(const QString &name)
{
    if (name == "euclidean") {
        return new EuclideanMetric();
    } else if (name == "manhattan") {
        return new ManhattanMetric();
    } else {
        return nullptr;
    }
}
