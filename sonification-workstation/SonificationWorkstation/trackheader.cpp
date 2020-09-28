#include "trackheader.h"

TrackHeader::TrackHeader(QWidget *parent) : QWidget(parent)
{

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *processingLayout = new QVBoxLayout;
    alphaSpinBox_ = new QSpinBox;
    procComboBox_ = new QComboBox;

    // Data processing section.
    QLabel *procLabel = new QLabel;
    procLabel->setText("Data smoothing:");
    QLabel *alphaLabel = new QLabel;
    QPixmap pixmap;
    if (!pixmap.load( ":/images/alpha.png" )) {
        qDebug("Failed to load images/target.png");
    }
    alphaLabel->setPixmap(pixmap);
    alphaLabel->setScaledContents(true);
    alphaLabel->setFixedSize(14, 14);

    QHBoxLayout *alphaLayout = new QHBoxLayout;
    alphaLayout->addWidget(alphaLabel);
    alphaLayout->addWidget(alphaSpinBox_);

    procComboBox_->setAccessibleName("Data smoothing dropdown, selects smoothing applied to data track during playback.");
    procComboBox_->setAccessibleDescription("");
    procComboBox_->addItem("None");
    procComboBox_->addItem("Simple Average");
    procComboBox_->addItem("Exponential Average");
    processingLayout->setContentsMargins(4,4,4,4);
    processingLayout->addWidget(procLabel);
    processingLayout->addWidget(procComboBox_);
    processingLayout->addLayout(alphaLayout);

    // Stylesheet.
    this->setObjectName("TrackHeader");
    this->setAutoFillBackground(true);
    alphaSpinBox_->setObjectName("AlphaSpinBox");
    procComboBox_->setObjectName("ProcComboBox");
    procLabel->setObjectName("ProcLabel");

    // Add everything to main layout.
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(2);
    mainLayout->addLayout(processingLayout);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    // connect signals and slots
    connect(procComboBox_, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(on_processingChanged(QString)));

}

void TrackHeader::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TrackHeader::on_processingChanged(QString text)
{

}
