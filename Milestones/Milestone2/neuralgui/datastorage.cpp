#include "datastorage.h"

DataStorage::DataStorage(QObject *parent) : QObject(parent)
{}

void DataStorage::acceptNewDatapoint(QString plotName, double xvalue, double yvalue)
{
    data[plotName].first.append(xvalue);
    data[plotName].second.append(yvalue);

    emit dataChanged();
}
