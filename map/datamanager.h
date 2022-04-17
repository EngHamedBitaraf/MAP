#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include <QObject>
#include <QAbstractListModel>
class DataManager : public QObject
{
    Q_OBJECT
public:
    explicit DataManager(QObject *parent = nullptr);

public slots :
    int getzoom();
    void setzoom(int value);


signals:

private:
    int zoom=10;
};

#endif // DATAMANAGER_H
