#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>

#include <marble/GeoDataPlacemark.h>
#include <marble/GeoDataStyle.h>
#include <marble/GeoDataIconStyle.h>
#include <marble/GeoDataDocument.h>
#include <marble/MarbleModel.h>
#include <marble/GeoDataTreeModel.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_marbleWidget(new MyMarbleWidget),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_marbleWidget);
    setLayout(layout);

    // Load the OpenStreetMap map
    m_marbleWidget->setMapThemeId("earth/openstreetmap/openstreetmap.dgml");
    m_marbleWidget->setProjection( Mercator );
    setGeometry(80, 60, 1000, 800);
    GeoDataCoordinates Tehran(51.41, 35.68, 0.0, GeoDataCoordinates::Degree);
    m_marbleWidget->centerOn(Tehran);
    m_marbleWidget->setZoom(1700);

    m_airplane = new GeoDataPlacemark("Airplan");
    GeoDataStyle *styleAirplane = new GeoDataStyle;
    GeoDataIconStyle iconStyle;
    iconStyle.setIconPath("/home/mosi/Desktop/airplan.png");
    iconStyle.setSize(QSize(45,45));
    styleAirplane->setIconStyle(iconStyle);
    m_airplane->setStyle(GeoDataStyle::Ptr( styleAirplane ));

    m_airplane->setCoordinate(Tehran);
    GeoDataDocument *document = new GeoDataDocument;

    document->append(m_airplane);
    document->append(m_airplane);

    m_marbleWidget->model()->treeModel()->addDocument(document);

    setCentralWidget(m_marbleWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    GeoDataCoordinates Tehran(51.41, 35.68, 0.0, GeoDataCoordinates::Degree);

    m_thread = new QThread;
    m_worker = new Worker(Tehran, (qreal)1, (qreal)0.05);
    m_worker->moveToThread(m_thread);

    connect(m_worker, SIGNAL(coordinatesChanged(GeoDataCoordinates)),
            this, SLOT(setCoordinates(GeoDataCoordinates)), Qt::BlockingQueuedConnection);


    connect(m_thread, SIGNAL(started()), m_worker, SLOT(startWork()));
    connect(m_thread, SIGNAL(finished()), m_worker, SLOT(finishWork()));

    m_thread->start();
}

void MainWindow::setCoordinates(const GeoDataCoordinates &coord)
{
    Worker *worker = qobject_cast<Worker*>(sender());
    if (worker == m_worker) {
//        m_count++;
//        if(m_count % 50 == 0 && m_marbleWidget->path.length()<50)
//            m_marbleWidget->path.append(coord);
        m_airplane->setCoordinate(coord);
        m_marbleWidget->model()->treeModel()->updateFeature(m_airplane);
    }
}

