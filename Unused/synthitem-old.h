#ifndef SYNTHITEM_H
#define SYNTHITEM_H

#include <atomic>
#include <vector>
#include <algorithm>
#include <memory>

#include "frame.h"
#include "ringbuffer.h"
#include "Gamma/Oscillator.h"
#include "dataset.h"

// Library definitions
#define MAX_DIMENSIONS 128
#define FRAME_RATE 44100

namespace sow {

class SynthItem
{
public:

    enum class ITEM {
        TRANSPORT,
        OSCILLATOR,
        AUDIFIER,
        MODULATOR,
        PANNER,
        ENVELOPE,
        VOLUME,
        NOISE,
        EQUALIZER
    };

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
        NOISE,
        RESONANCE,
        FILTER_TYPE
    };

    enum class ITEM_CMD {
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

    enum class NOISE {
        WHITE,
        PINK
    };

    enum class FILTER_TYPE {
        LOW_PASS,
        HIGH_PASS,
        PEAK,
        NOTCH
    };

    struct ItemCommand {
        ITEM_CMD type;
        PARAMETER parameter;
        Dataset *dataset;
        std::vector<float>* data;
        std::vector<float>* mins;
        std::vector<float>* maxes;
        std::vector<float> doubles;
        std::vector<int> ints;
        bool bool_val;
        SynthItem* item;
        ItemCommand() {
            doubles.reserve(MAX_DIMENSIONS);
            ints.reserve(MAX_DIMENSIONS);
        }
    };

    explicit SynthItem() {}
    virtual ~SynthItem() {}
    virtual void delete_self() = 0;
    virtual ITEM get_type() = 0;
    virtual void set_data(std::vector<double>* data,
                             std::vector<double>* mins,
                             std::vector<double>* maxes) = 0;
    virtual void add_parent(SynthItem* parent) = 0;
    virtual void remove_parent(SynthItem* parent) = 0;
    virtual bool add_child(SynthItem *child, PARAMETER param) = 0;
    virtual void remove_child(SynthItem *child) = 0;
    virtual void mute(bool mute) = 0;
    virtual Frame process() = 0; // every sample
    virtual void step() = 0; // every new data value (step)
    virtual void control_process() = 0; // every process block

    virtual bool get_mute() = 0;
    virtual std::vector<SynthItem*> get_parents() = 0;

protected:

    virtual void retrieve_commands() = 0;
    virtual void process_command(ItemCommand command) = 0;
    virtual void process_add_child(SynthItem* child, PARAMETER parameter) = 0;
    virtual void process_remove_child(SynthItem* child) = 0;
    virtual void process_delete() = 0;

};

} // namespace sow

#endif // SYNTHITEM_H