#include "MetricFactory.h"
#include "EuclideanMetric.h"
#include "ManhattanMetric.h"
#include "ChebyshevMetric.h"
#include "NormalizedMetric.h"

#include <QString>

MetricInterface *MetricFactory::getNewMetric(const QString &name)
{
    if (name == "euclidean") {
        return new EuclideanMetric();
    } else if (name == "manhattan") {
        return new ManhattanMetric();
    } else if (name == "chebyshev") {
        return new ChebyshevMetric();
    } else if (name == "normalized") {
        return new NormalizedMetric();
    } else {
        return nullptr;
    }
}
