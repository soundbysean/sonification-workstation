#include "synthwindow.h"
#include "ui_synthwindow.h"

SynthWindow::SynthWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SynthWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Sonification Workstation: Synthesis");

}

SynthWindow::~SynthWindow()
{
    delete ui;
}

QQuickView *SynthWindow::getView() const
{
    return view;
}

void SynthWindow::setView(QQuickView *inView)
{
    view = inView;
    QWidget *container = QWidget::createWindowContainer(view, this);
    view->setSource(QUrl("qrc:/main.qml")); // Fetch this url by right clicking on your resource file.
    ui->verticalLayout->addWidget(container);
}
