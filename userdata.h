#ifndef USERDATA_H
#define USERDATA_H

#endif // USERDATA_H

#include "synthgraph.h"
#include "Gamma/Oscillator.h"

namespace son {

typedef struct {
    SynthGraph* graph;
    gam::Sine<>* gen;

} UserData;

} //namespace son
