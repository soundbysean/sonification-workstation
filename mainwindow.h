#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QtCharts>
#include <QAction>
#include <QTabWidget>
#include <QLayout>
#include <QQmlContext>
#include <QQuickView>

#include <atomic>

//#include "scatterview.h"
//#include "lineview.h"
#include "qttransport.h"
#include "transportwidget.h"
#include "filereader.h"
#include "qcustomplot.h"
#include "plotter.h"

using namespace QtCharts;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QtTransport* getTransport();

private:

    std::vector<double> dataset;
    QtTransport* qtTransport;
    FileReader* fileReader;

    //Tab widget and tabs
    QTabWidget* tabWidget;
    QWidget* tableTab;
    QWidget* lineTab;
    QWidget* scatterTab;
    //Tab widget layouts
    QLayout* tableTabLayout;
    QLayout* lineTabLayout;
    QLayout* scatterTabLayout;
    //transport stuff
    QWidget* transportWidget;
    QLayout* transportLayout;
    QPushButton* orientationButton;
    QPushButton* playButton;
    //Main graphical widgets
    QTableView* tableView;
    Plotter* plotter;

    //convenience functions to create and populate menus
    void createActions();
    void createMenus();
    //menus and actions
    QMenu *fileMenu;
    QAction* importCSVAct;

private slots:
    void quit();
    void openDataset();

signals:

};

#endif // MAINWINDOW_H
