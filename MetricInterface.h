#ifndef METRICINTERFACE_H
#define METRICINTERFACE_H

#include <QVector>

class MetricInterface {
public:
    virtual ~MetricInterface();
    virtual double distance(const QVector<double> &vect1, const QVector<double> &vect2) const = 0;
};

#endif // METRICINTERFACE_H
