#ifndef AUDIFIER_H
#define AUDIFIER_H

#include <algorithm>

#include "utility.h"
#include "synthitem.h"
#include "ringbuffer.h"

namespace son {

class Audifier final : public SynthItem
{

public:
    Audifier();
    ~Audifier();
    // helper when deleting item contained in synth tree
    void delete_self() override;
    // interface overrides
    ITEM get_type() override;
    void set_data(std::vector<double>* data,
                  std::vector<double>* mins,
                  std::vector<double>* maxes) override;
    void add_parent(SynthItem* parent) override;
    void remove_parent(SynthItem* parent) override;
    bool add_child(SynthItem *child, PARAMETER param) override;
    void remove_child(SynthItem *child) override;
    void mute(bool mute) override;
    // audification source
    void set_aud_indexes(std::vector<int> indexes);

    // getters are not thread-safe
    bool get_mute();
    std::vector<SynthItem*> get_parents();
    // audification parameter getters
    std::vector<int> get_aud_indexes();

    // generate a frame
    Frame process() override; // every sample
    void step() override; // every new data value (step)
    void control_process() override; // every process block

private:
    void retrieve_commands() override;
    void process_command(SynthItemCommand command);
    void process_add_child(SynthItem* child, PARAMETER param) override;
    void process_remove_child(SynthItem* child) override;
    void process_delete() override;

    void process_set_data(std::vector<double>* data, std::vector<double>* mins, std::vector<double>* maxes);
    void process_set_param_indexes(std::vector<int> indexes, PARAMETER param);

    ITEM my_type_;
    PARAMETER my_child_type_;
    RingBuffer<SynthItemCommand> command_buffer_;
    SynthItemCommand current_command_;
    std::vector<SynthItem::PARAMETER> accepted_children_;
    std::vector<double>* data_;
    std::vector<double>* mins_;
    std::vector<double>* maxes_;
    std::vector<SynthItem*> parents_;
    std::vector<SynthItem*> amods_;
    std::vector<int> audify_indexes_;
    bool muted_;
};

}

#endif // AUDIFIER_H
