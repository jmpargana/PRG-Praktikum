#include "datastorage.h"

DataStorage::DataStorage(QObject *parent) : QObject(parent)
{}

void DataStorage::acceptNewDatapoint(QString plotName, double xvalue, double yvalue)
{
    data[plotName].first.resize(data[plotName].first.size() + 1);
    data[plotName].second.resize(data[plotName].second.size() + 1);
    data[plotName].first.append(xvalue);
    data[plotName].second.append(yvalue);
}
