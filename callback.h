#ifndef CALLBACK_H
#define CALLBACK_H

#endif // CALLBACK_H

#include <QDebug>
#include "userdata.h"


namespace son {

// Two-channel sawtooth wave generator.
int callback( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
              double streamTime, RtAudioStreamStatus status, void *data )
{
    Q_UNUSED(streamTime)
    Q_UNUSED(inputBuffer)

    double *buffer = (double *) outputBuffer;
    UserData* uData = (UserData *) data;
    SynthGraph* graph = uData->graph;


    if ( status )
        std::cout << "Stream underflow detected!" << std::endl;


    // Write interleaved audio data.
    for (unsigned int i=0; i < nBufferFrames; ++i) {

        float s = graph->processGraph();
        s *= 0.1;
        *buffer++ = s;
        *buffer++ = s;

        //test noise
        //*buffer++ = ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;
        //test mssg
        //qDebug() << "callback";
    }
    return 0;

}

} //namespace son
