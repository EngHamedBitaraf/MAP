#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datamanager.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    d = new DataManager;
    view = new QQuickView (QUrl(QLatin1String("qrc:/main.qml")));
    view->engine()->rootContext()->setContextProperty("Datamanger",d);
    qmlwidget =QWidget::createWindowContainer (view);
    ui->horizontalLayout->addWidget(qmlwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    d->setzoom(value);
    //qDebug()<<QString::number(value);
}

