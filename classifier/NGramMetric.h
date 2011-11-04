#ifndef NGRAMMETRIC_H
#define NGRAMMETRIC_H

#include "MetricInterface.h"

class NGramMetric : public MetricInterface
{
public:
    QVector<Element> loadData(const QStringList &arguments) const;
    double distance(const Element &e1, const Element &e2) const;
    void clean(const QVector<Element> &elements) const;
};

#endif // NGRAMMETRIC_H
