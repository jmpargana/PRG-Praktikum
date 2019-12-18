#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QObject>
#include <QtCore/QHash>
#include <QtCore/QString>
#include <QtCore/QPair>
#include <QtCore/QVector>

class DataStorage : public QObject
{
    Q_OBJECT
public:
    explicit DataStorage(QObject *parent = nullptr);

signals:

public slots:
    void acceptNewDatapoint(QString plotName, double xvalue, double yvalue);

public:
    QHash< QString, QPair< QVector<double>, QVector<double> > > data;
};

#endif // DATASTORAGE_H
