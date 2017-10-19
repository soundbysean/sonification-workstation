#include "trackview.h"

TrackView::TrackView(QWidget *parent) : QWidget(parent)
{
    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::red);
    this->setAutoFillBackground(true);
    this->setPalette(pal);
}

void TrackView::setPlayHead(PlayHead *p)
{
    playHead = p;
}
