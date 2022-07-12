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
    m_marbleWidget->setProjection( Marble::Mercator );
    setGeometry(80, 60, 1000, 800);
    GeoDataCoordinates Tehran(51.41, 35.68, 0.0, GeoDataCoordinates::Degree);
    m_marbleWidget->centerOn(Tehran);
    m_marbleWidget->setZoom(1700);

    m_airplane = new GeoDataPlacemark("Airplan");
    GeoDataStyle *styleAirplane = new GeoDataStyle;
    GeoDataIconStyle iconStyle;
    iconStyle.setIconPath("/home/client110/Desktop/airplan.png");
    iconStyle.setSize(QSize(45,45));
    styleAirplane->setIconStyle(iconStyle);
    m_airplane->setStyle(GeoDataStyle::Ptr( styleAirplane ));

    m_airplane->setCoordinate(Tehran);
    m_airplane->setPopulation( 1877155 );
    m_airplane->setCountryCode ( "Romania" );
    GeoDataDocument *document = new GeoDataDocument;

    document->append(m_airplane);
//    document->append(m_airplane);
    //m_marbleWidget->model()->treeModel()->addDocument(document);

    for(int i = 0; i < 100; i++)
    {
        GeoDataPlacemark *gp = new GeoDataPlacemark("Airplan" + QString::number(i));
        GeoDataCoordinates cor(51.41 + i+1, 35.68 + i, 0.0, GeoDataCoordinates::Degree);
        GeoDataStyle *styleAirplane1 = new GeoDataStyle;
        GeoDataIconStyle iconStyle1;
        iconStyle1.setIconPath("/home/client110/Desktop/airplan.png");
        iconStyle1.setSize(QSize(45,45));
        styleAirplane1->setIconStyle(iconStyle1);
        gp->setStyle(GeoDataStyle::Ptr( styleAirplane1 ));
        gp->setCoordinate(cor);
//        GeoDataDocument *d = new GeoDataDocument;
        document->append(gp);

    }

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

