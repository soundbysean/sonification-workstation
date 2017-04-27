#ifndef CALLBACK_H
#define CALLBACK_H

#endif // CALLBACK_H

#include <QDebug>
#include "userdata.h"

namespace son {

int callback( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
              double streamTime, RtAudioStreamStatus status, void *data )
{
    Q_UNUSED(streamTime)
    Q_UNUSED(inputBuffer)

    UserData* uData = (UserData *) data;
    double *buffer = (double *) outputBuffer;
    QtTransport* graph = uData->tranpsport;
//    Sequencer* sequencer = uData->seq;

    if ( status )
        std::cout << "Stream underflow detected!" << std::endl;


    // Write interleaved audio data.
    for (unsigned int i=0; i < nBufferFrames; ++i) {

        float s = graph->process();
        s *= 0.1;
        *buffer++ = s;
        *buffer++ = s;

        //test noise
//        *buffer++ = ((qrand() * 1.0 / RAND_MAX) - 1.0) * 0.2;
        //test mssg
//        qDebug() << "callback";
    }

//    qDebug() << "cb: " << qrand();

//    sequencer->fillRingBuffer();

    return 0;

}

} //namespace son
