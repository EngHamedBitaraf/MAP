#ifndef WORKER_H
#define WORKER_H

#include <marble/MarbleWidget.h>
#include <QWidget>
#include <QThread>
#include <QTimer>
#include <QHash>
#include <qmath.h>
using namespace Marble;

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker(const GeoDataCoordinates& city, qreal radius, qreal speed);

signals:
    void coordinatesChanged(GeoDataCoordinates coord);

public slots:
    void startWork();
    void finishWork();

private slots:
    void iterate();

private:
    QTimer *m_timer;
    GeoDataCoordinates m_city;
    qreal m_radius;
    qreal m_speed;
    qreal m_alpha;
};


#endif // WORKER_H
