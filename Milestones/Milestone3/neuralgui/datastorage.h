#ifndef DATASTORAGE_H
#define DATASTORAGE_H

#include <QObject>
#include <QtCore/QHash>
#include <QtCore/QString>
#include <QtCore/QPair>
#include <QtCore/QVector>

/**
 * a data storage for the data to display as graphs
 */
class DataStorage : public QObject
{
    Q_OBJECT
public:
    explicit DataStorage(QObject *parent = nullptr);

signals:
    // if the data was changed (by emiting another signal) this signal triggers the graph to update
    void dataChanged();

public slots:
    void acceptNewDatapoint(QString plotName, double xvalue, double yvalue);

public:
    // the actual storage, where eg. in "time" the x/y coords for the time/epoch is saved
    QHash< QString, QPair< QVector<double>, QVector<double> > > data;
};

#endif // DATASTORAGE_H
