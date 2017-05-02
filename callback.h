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
    SynthItem* root = uData->root;

    if ( status )
        std::cout << "Stream underflow detected!" << std::endl;


    // Write interleaved audio data.
    for (unsigned int i=0; i < nBufferFrames; ++i) {

        float s = root->process();
        s *= 0.1;
        *buffer++ = s;
        *buffer++ = s;
    }

    return 0;

}

} // namespace son
