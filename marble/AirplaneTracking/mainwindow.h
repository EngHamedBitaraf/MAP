#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mymarblewidget.h"
#include "worker.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void start();
public slots:
    void setCoordinates(const GeoDataCoordinates &coord);
private:
    MyMarbleWidget *m_marbleWidget;
    GeoDataPlacemark *m_airplane;
    Worker *m_worker;
    QThread *m_thread;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
