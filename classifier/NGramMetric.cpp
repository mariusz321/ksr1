#undef __STRICT_ANSI__
#include "NGramMetric.h"
#include "NGramLoader.h"

#include <QStringList>

#include <QDebug>

double NGramMetric::distance(const Element &e1, const Element &e2) const
{
    int sum = 0;
    //int all = 0;
    for (QHash<QString, int>::const_iterator it1 = e1.ngrams->constBegin(); it1 != e1.ngrams->constEnd(); it1++) {
        //all += it1.value();
        for (QHash<QString, int>::const_iterator it2 = e2.ngrams->constBegin(); it2 != e2.ngrams->constEnd(); it2++) {
            //all += it2.value();
            if (it1.key() == it2.key()) {
                sum += it1.value() + it2.value();
            }
        }
    }
    //qDebug() << "all:" << all << e1.ngramSizes->at(1) + e2.ngramSizes->at(1);
    double result = 1.0 - (double(sum) / (double(e1.ngramSizes->at(1) + e2.ngramSizes->at(1)) - e1.ngramSizes->at(0) + 1));
    return result;
}

QVector<Element> NGramMetric::loadData(const QStringList &arguments, const bool &normalize) const
{
    return NGramLoader::loadData(QStringList() << "output_100.dat");
}

void NGramMetric::clean(const QVector<Element> &elements) const
{
    NGramLoader::clean(elements);
}
