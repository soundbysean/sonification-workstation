#ifndef PANNER_H
#define PANNER_H

#include "synthitem.h"

namespace son {

class Panner : public SynthItem
{
public:
    Panner();

    // helper when deleting item contained in synth tree
    void delete_item() override;
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
    // pan parameter accessors
    void set_pan(double pan);
    void set_pan_fixed(bool fixed);
    void set_pan_indexes(std::vector<int> indexes);
    void set_pan_scaled(bool scaled);
    void set_pan_scale_vals(double low,
                             double high,
                             double exp);

    // generate a frame
    Frame process() override;

private:
    void retrieve_commands() override;
    void process_command(SynthItemCommand command) override;
    void process_add_child(SynthItem* child, PARAMETER parameter) override;
    void process_remove_child(SynthItem* child) override;
    void process_delete_item() override;

    void process_set_data(std::vector<double>* data,
                          std::vector<double>* mins,
                          std::vector<double>* maxes);
    void process_set_param_value(double val, PARAMETER param);
    void process_set_param_fixed(bool fixed, PARAMETER param);
    void process_set_param_indexes(std::vector<int> indexes, PARAMETER param);
    void process_set_param_scaled(bool scaled, PARAMETER param);
    void process_set_param_scale_vals(double low,
                                      double high,
                                      double exp,
                                      PARAMETER param);

    double calculate_pan_pos();

    ITEM my_type_;
    RingBuffer<SynthItemCommand> command_buffer_;
    SynthItemCommand current_command_;
    std::vector<SynthItem::PARAMETER> accepted_children_;
    std::vector<double>* data_;
    std::vector<double>* mins_;
    std::vector<double>* maxes_;
    std::vector<SynthItem*> parents_;
    std::vector<SynthItem*> inputs_;
    std::vector<SynthItem*> amods_;
    std::vector<int> pan_indexes_;
    bool muted_;

    //for scaling the data to intended pan values
    double pan_;
    bool pan_fixed_;
    bool pan_scaled_;
    double pan_low_;
    double pan_high_;
    double pan_exponent_;
};

} // namespace son

#endif // PANNER_H