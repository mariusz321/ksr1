#include "NGramMetric.h"
#include "NGramLoader.h"

#include <QStringList>

double NGramMetric::distance(const Element &e1, const Element &e2) const
{
    int sum = 0;
    for (QHash<QString, int>::const_iterator it1 = e1.ngrams->constBegin(); it1 != e1.ngrams->end(); it1++) {
        for (QHash<QString, int>::const_iterator it2 = e2.ngrams->constBegin(); it2 != e2.ngrams->end(); it2++) {
            if (it1.key() == it2.key()) {
                ++sum;
            }
        }
    }
    double result = 1.0 - (double(sum) / (double(e1.ngrams->size()) - e1.ngramSizes->at(0) + 1));
    return result;
}

QVector<Element> NGramMetric::loadData(const QStringList &arguments) const
{
    return NGramLoader::loadData(QStringList() << "output_100.dat");
}

void NGramMetric::clean(const QVector<Element> &elements) const
{
    NGramLoader::clean(elements);
}
