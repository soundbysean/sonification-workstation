#include "trackview.h"

namespace sow {

TrackView::TrackView(QWidget *parent) : QWidget(parent)
{

    QHBoxLayout* centralLayout = new QHBoxLayout(this); // Top-level layout for this widget
    QWidget* plotsContainer = new QWidget(this);        // Widget for TrackPlotters layout
    QWidget* tracksContainer = new QWidget(this);       // Widget for Tracks layout (headers)
    QWidget* stackedContainer = new QWidget(this);      // Widget for StackedLayouts of TrackPlotters and PlayHead
    stackedLayout_ = new QStackedLayout(this);          // Layout with TrackPlotters behind PlayHead
    plotsLayout_ = new QVBoxLayout(this);               // Layout for the TrackPlotters
    tracksLayout_ = new QVBoxLayout(this);              // Layout for the Tracks (headers)

    stackedLayout_->setStackingMode(QStackedLayout::StackingMode::StackAll);

    // Set margins and spacing
    centralLayout->setContentsMargins(Margin, Margin, Margin, Margin);
    centralLayout->setSpacing(0);
    plotsLayout_->setContentsMargins(0, 0, 0, 0);
    plotsLayout_->setSpacing(TrackSpacing);
    tracksLayout_->setContentsMargins(0, 0, 0, 0);
    tracksLayout_->setSpacing(TrackSpacing);

    // Add layouts to respective containers
    plotsContainer->setLayout(plotsLayout_);
    tracksContainer->setLayout(tracksLayout_);
    stackedContainer->setLayout(stackedLayout_);
    stackedLayout_->addWidget(plotsContainer);
    centralLayout->addWidget(tracksContainer);
    centralLayout->addWidget(stackedContainer);
    this->setLayout(centralLayout);

    // set background color
    QPalette* pal = new QPalette;
    pal->setColor(QPalette::Background, QColor("light grey"));
    this->setAutoFillBackground(true);
    this->setPalette(*pal);
}

void TrackView::setPlayHead(PlayHead *playHead)
{
    playHead_ = playHead;
    connect(this, &TrackView::xRangeChanged,
            playHead_, &PlayHead::onXRangeChanged);
    // Create a layout and container for the PlayHead
    QWidget* container = new QWidget(this);
    playheadLayout_ = new QHBoxLayout(this);
    // Margin to the left ensures Playheead lines up
    // with the start of the track plot, not the header
    playheadLayout_->setContentsMargins(0, 0, 0, 0);
    playheadLayout_->addWidget(playHead_);
    container->setLayout(playheadLayout_);
    // Insert playhead container into the stacked
    // layout and bring it to the front
    stackedLayout_->addWidget(container);
    stackedLayout_->setCurrentWidget(container);
}

///
/// \brief TrackView::wheelEvent
/// \param e
/// Transmit wheel events to all tracks
/// so they can set their zoom level
void TrackView::wheelEvent(QWheelEvent *e)
{
    emit wheelChanged(e);
}

void TrackView::plot(sow::Dataset *dataset)
{
    for(int i = 0; i < dataset->cols(); i++)
    {
        // add tracks
        Track* track = addTrack();
        track->setTrackNumber(i + 1);
        // plot to each track
        std::vector<float> trackData = dataset->getCol(i);
        track->plot(trackData);
    }
    plotsLayout_->addStretch();
    tracksLayout_->addStretch();
}

void TrackView::clear()
{
    QLayoutItem* child;
    // Delete tracksLayout_ items and tracks.
    // Tracks will delete their plotters.
    while (tracksLayout_->count() != 0)
    {
        child = tracksLayout_->takeAt(0);
        QWidget* widget = child->widget();
        if(widget != nullptr)
        {
            delete widget;
        }
        delete child;
    }

    // Ensure all non-track items are
    // cleared from PlotsLayout.
    while (plotsLayout_->count() != 0)
    {
        child = plotsLayout_->takeAt(0);
        delete child;
    }
}

Track *TrackView::addTrack()
{
    Track* track = new Track(this);
    TrackPlotter* plotter = new TrackPlotter(track);
    track->setPlotter(plotter);
    plotsLayout_->addWidget(plotter);
    tracksLayout_->addWidget(track);

    connect(track, &Track::xRangeChanged,
            this, &TrackView::onXRangeChanged);
    connect(this, &TrackView::xRangeChanged,
            track, &Track::onXRangeChanged);
    connect(this, &TrackView::wheelChanged,
            plotter, &TrackPlotter::onWheelChanged);

    return track;
}

void TrackView::onDatasetChanged(sow::Dataset* dataset)
{
    clear();
    plot(dataset);
}

void TrackView::onXRangeChanged(QCPRange range)
{
    emit xRangeChanged(range);
}

} // namespace sow