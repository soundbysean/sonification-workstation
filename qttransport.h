#ifndef QTTRANSPORT_H
#define QTTRANSPORT_H

#include <QObject>

#include "transport.h"
#include "qtoscillator.h"
#include "qtaudifier.h"
#include "qtmodulator.h"
#include <QTimer>

using namespace son;

class QtTransport : public QObject
{
    Q_OBJECT
    Q_ENUMS(ITEM)
public:

    enum ITEM {
        OUT = (int)SynthItem::ITEM::OUT,
        OSCILLATOR,
        AUDIFIER,
        MODULATOR
    };

    explicit QtTransport(QObject *parent = 0);

    Q_INVOKABLE QtSynthItem* createItem(ITEM type);
    float process();
    int graphSize();

public slots:
    // slots for controlling playback
    void on_pauseChanged(bool on_pauseChanged);
    void on_posChanged(double pos);
    void on_speedChanged(double speed);
    void on_loopingChanged(bool looping);
    void on_loopPointsChanged(double begin, double end);
    void on_dataChanged(std::vector<double>* data, unsigned int height, unsigned int width);
    void on_interpolateChanged(bool interpolate);

    // for polling state from outside
    // (i.e. GUI)
    double getPos();

private:
    Transport transport;

signals:
    void cursorPosChanged(double pos);

private slots:
    void updateCursorPos();

};

#endif // QTTRANSPORT_H
