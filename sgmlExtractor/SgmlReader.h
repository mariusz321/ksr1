#ifndef SGMLREADER_H
#define SGMLREADER_H

#include <QDir>
#include <QPair>

class SgmlReader
{
    QRegExp tagRegExp;
    QRegExp tagRegExp2;
    QRegExp bodyStartRegExp;
    QRegExp bodyStartRegExp2;
    QRegExp bodyEndRegExp;
    QStringList labelsList;
public:
    SgmlReader(QStringList, QString);
    QList<QPair<QString, QString> > readDirectory(QString);
};

#endif // SGMLREADER_H
