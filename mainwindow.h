#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QQmlContext>
#include <QQuickView>
#include <QAction>
#include <QLayout>

#include "trackview.h"
#include "qttransport.h"
#include "transportwidget.h"
#include "filereader.h"
#include "session.h"

using namespace sow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QtTransport* getTransport();

private:

    QtTransport* transport;
    Session* session;

    //convenience functions to create and populate menus
    void createActions();
    void createMenus();

private slots:

    void onQuit();

};

#endif // MAINWINDOW_H
