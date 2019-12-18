#include "datastorage.h"

DataStorage::DataStorage(QObject *parent) : QObject(parent)
{}

void DataStorage::acceptNewDatapoint(QString plotName, double xvalue, double yvalue)
{
    // write new datapoints to storage
    data[plotName].first.append(xvalue);
    data[plotName].second.append(yvalue);

    // trigger the gui to update
    emit dataChanged();
}
