#include "datamanager.h"
#include <QCoreApplication>

DataManager::DataManager(QObject *parent) : QObject(parent)
{

}

void DataManager::close()
{
    qApp->exit();
}


