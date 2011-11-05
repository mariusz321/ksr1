#undef __STRICT_ANSI__
#include "MetricFactory.h"
#include "EuclideanMetric.h"
#include "ManhattanMetric.h"
#include "ChebyshevMetric.h"
#include "NormalizedMetric.h"
#include "NGramMetric.h"

#include <QString>

MetricInterface *MetricFactory::getNewMetric(MetricFactory::Metric metric)
{
    switch(metric){
        case EUCLIDEAN:
            return new EuclideanMetric();
        case MANHATTAN:
            return new ManhattanMetric();
        case CHEBYSHEV:
            return new ChebyshevMetric();
        case NORMALIZED:
            return new NormalizedMetric();
        default:
            return new NGramMetric();
    }
}
