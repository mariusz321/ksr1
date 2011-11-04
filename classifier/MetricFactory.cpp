#include "MetricFactory.h"
#include "EuclideanMetric.h"
#include "ManhattanMetric.h"
#include "ChebyshevMetric.h"
#include "NormalizedMetric.h"
#include "NGramMetric.h"

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
    } else if (name == "ngram") {
        return new NGramMetric();
    } else {
        return nullptr;
    }
}
