#ifndef SOWENUMS_H
#define SOWENUMS_H
#include <QObject>

namespace sow {

namespace sowenums {

Q_NAMESPACE
enum ITEM {
    OUT,
    OSCILLATOR,
    AUDIFIER,
    MODULATOR,
    PANNER,
    ENVELOPE,
    VOLUME,
    NOISE,
    EQUALIZER,
    TRANSPORT
};
Q_ENUM_NS(ITEM)

Q_NAMESPACE
enum class PARAMETER {
    INPUT,
    OUTPUT,
    AMPLITUDE,
    FREQUENCY,
    DEPTH,
    AUDIFICATION,
    PAN,
    ATTACK,
    DECAY,
    VOLUME,
    NOISE_TYPE,
    RESONANCE,
    FILTER_TYPE
};
Q_ENUM_NS(PARAMETER)

Q_NAMESPACE
enum class SUB_PARAMETER {
    VALUE,
    FIXED,
    SCALED,
    SCALE_HI,
    SCALE_LO,
    SCALE_EXP,
    MAP
};
Q_ENUM_NS(SUB_PARAMETER)

Q_NAMESPACE
enum class NOISE_TYPE {
    WHITE,
    PINK
};
Q_ENUM_NS(NOISE_TYPE)

Q_NAMESPACE
enum class FILTER_TYPE {
    LOW_PASS,
    HIGH_PASS,
    PEAK,
    NOTCH
};
Q_ENUM_NS(FILTER_TYPE)

enum class COMMAND {
    DATA,
    ADD_CHILD,
    REMOVE_CHILD,
    ADD_PARENT,
    REMOVE_PARENT,
    MUTE,
    PARAM,
    FIXED,
    INDEXES,
    SCALED,
    SCALE_LOW,
    SCALE_HIGH,
    SCALE_EXPONENT,
    DELETE,
    DELETE_ITEM,
    MODULATION,
    NOISE,
    FILTER_TYPE,
    PAUSE,
    POSITION,
    SPEED,
    LOOP,
    LOOP_POINTS,
    INTERPOLATE,
    SUBSCRIBE,
    UNSUBSCRIBE
};

} // Namespace sowenums.

} // Namespace sow.

#endif // SOWENUMS_H
