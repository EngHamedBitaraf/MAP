#include "datamanager.h"

DataManager::DataManager(QObject *parent) : QObject(parent)
{

}

int DataManager::getzoom()
{
    return zoom;
}

void DataManager::setzoom(int value)
{
    zoom=value;
}
