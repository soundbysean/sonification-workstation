#ifndef TRACKHEADER_H
#define TRACKHEADER_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QPixmap>
#include <QBitmap>
#include <QPainter>

class TrackHeader : public QWidget
{
    Q_OBJECT
public:
    explicit TrackHeader(QWidget *parent = nullptr);

private:

    uint trackNumber_;
    QComboBox *procComboBox_;
    QSpinBox *alphaSpinBox_;

protected:

    void paintEvent(QPaintEvent* event) override;

signals:

public slots:

private slots:
    void on_processingChanged(QString text);

};

#endif // TRACKHEADER_H
