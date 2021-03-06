#ifndef SOWENUMS_H
#define SOWENUMS_H
#include <QObject>

class ENUMS : public QObject
{
    Q_OBJECT

public:

    enum class ITEM_TYPE {
        NONE,
        OSCILLATOR,
        AUDIFIER,
        AMOD,
        FMOD,
        PANNER,
        ENVELOPE,
        VOLUME,
        NOISE_GEN,
        EQUALIZER,
        TRANSPORT
    };
    Q_ENUM(ITEM_TYPE)

    enum class OUTPUT_TYPE {
        NONE,
        AM,
        FM,
        AUDIO
    };
    Q_ENUM(OUTPUT_TYPE)

    enum class PARAMETER {
        AMPLITUDE,
        FREQUENCY,
        DEPTH,
        PAN,
        ATTACK,
        DECAY,
        LEVEL,
        NOISE_TYPE,
        RESONANCE,
        FILTER_TYPE
    };
    Q_ENUM(PARAMETER)

    enum class SUB_PARAMETER {
        SCALED,
        SCALE_OUT_LOW,
        SCALE_OUT_HIGH,
        SCALE_EXP,
        MAP,
        INDEX
    };
    Q_ENUM(SUB_PARAMETER)

    enum class NOISE {
        WHITE,
        PINK,
        BROWNIAN
    };
    Q_ENUM(NOISE)

    enum class FILTER {
        LOW_PASS,
        HIGH_PASS,
        BAND_PASS,
        NOTCH
    };
    Q_ENUM(FILTER)

    enum class ITEM_CMD {
        MUTE,
        UNMUTE,
        CONNECT_CHILD,
        CONNECT_PARENT,
        DISCONNECT,
        DISONNECT_ALL
    };

    enum class TRANSPORT_CMD {
        PAUSE,
        RECORD,
        POS,
        SPEED,
        LOOP,
        LOOP_PTS,
        SUB,
        UNSUB,
        DELETE_ITEM,
        IMPORT_DATASET,
        VOLUME,
        MUTE
    };

    enum class DATA_PROCESSOR_CMD {
        FLUSH,
        PROC_TYPE,
        INTERPOLATE,
        N_VAL
    };

    enum class PROCESSING_TYPE {
        NONE,
        SIMPLE,
        EXPONENTIAL
    };

};


#endif // SOWENUMS_H
