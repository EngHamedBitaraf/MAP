#include "worker.h"
Worker::Worker(const GeoDataCoordinates &city, qreal radius, qreal speed) :
    QObject(),
    m_timer(new QTimer(this)),
    m_city(city),
    m_radius(radius),
    m_speed(speed),
    m_alpha(0.0)
{}

void Worker::startWork()
{
    m_timer->setInterval(0);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(iterate()));
    m_timer->start();
}

void Worker::iterate()
{
    qreal lon = m_city.longitude(GeoDataCoordinates::Degree) + m_radius * qCos(m_alpha * DEG2RAD);
    qreal lat = m_city.latitude(GeoDataCoordinates::Degree) + m_radius * qSin(m_alpha * DEG2RAD);

    GeoDataCoordinates coord(lon, lat, 0.0, GeoDataCoordinates::Degree);
    emit coordinatesChanged(coord);

    m_alpha += m_speed;
}

void Worker::finishWork()
{
    m_timer->stop();
}
