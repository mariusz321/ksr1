#include "NGramLoader.h"

#include <QFile>
#include <QTextStream>
#include <QStringList>

#define NGRAM_SIZE 3

QVector<Element> NGramLoader::loadData(const QStringList &arguments)
{
    const QString fileName(arguments.at(0));
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QVector<Element> result;
    QVector<double> *sizes = new QVector<double>();
    sizes->append(NGRAM_SIZE);

    while (!in.atEnd()) {
        Element e;
        e.label = in.readLine();

        const QStringList words = in.readLine().split(' ', QString::SkipEmptyParts);
        QHash<QString, int> *ngrams = new QHash<QString, int>();
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words.at(i).size() - NGRAM_SIZE + 1; j++) {
                ++((*ngrams)[words.at(i).mid(j, NGRAM_SIZE)]);
            }
        }
        e.ngrams = ngrams;
        e.ngramSizes = sizes;
        result.append(e);
    }
    file.close();
    return result;
}

void NGramLoader::clean(const QVector<Element> &elements)
{
    for (int i = 0; i < elements.size(); i++) {
        delete elements.at(i).ngrams;
    }
    delete elements.at(0).ngramSizes;
}
