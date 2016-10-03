#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "synthitem.h"
#include "Gamma/Oscillator.h"

namespace son {

class Oscillator : public SynthItem
{
public:
    Oscillator();

    void addChild(QObject* child, int type);
    void removeChild(QObject* child);
    float process();

private:

    QVector<double> data;

    //for scaling the input
//    double dataMin;
//    double dataMax;
//    float freqMin;
//    float freqMax;

    gam::WaveformType waveType;
    gam::Sine<>* defaultGen;

    QVector<gam::Sine<>*> gens;
    QVector<SynthItem*> amods;
    QVector<SynthItem*> fmods;

    float visitFmods();
    float visitAmods();
    void setFreqs();
    void setAmps();

};

} //namespace son

#endif // OSCILLATOR_H
