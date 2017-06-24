#include "volume.h"
#include "utility.h"

namespace son {

Volume::Volume()
{
    my_type_ = ITEM::VOLUME;
    muted_ = false;
    volume_ = 1;
    volume_fixed_ = true;
    volume_scaled_ = true;
    volume_low_ = 0;
    volume_high_ = 1;
    volume_exponent_ = 1;

    accepted_children_ = {
        PARAMETER::INPUT,
        PARAMETER::AMPLITUDE
    };
}

void Volume::delete_item()
{
    SynthItemCommand command;
    command.type = COMMAND::DELETE;
    command_buffer_.push(command);
}

SynthItem::ITEM Volume::get_type()
{
    return my_type_;
}

void Volume::set_data(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    SynthItemCommand command;
    command.type = COMMAND::DATA;
    command.data = data;
    command.mins = mins;
    command.maxes = maxes;
    command_buffer_.push(command);
}

void Volume::add_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::ADD_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

void Volume::remove_parent(SynthItem *parent)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_PARENT;
    command.item = parent;
    command_buffer_.push(command);
}

bool Volume::add_child(SynthItem *child, SynthItem::PARAMETER param)
{
    if(!verify_child(param, accepted_children_))
    {
        return false;
    }
    SynthItemCommand command;
    command.type = COMMAND::ADD_CHILD;
    command.parameter = param;
    command.item = child;
    command_buffer_.push(command);
    return true;
}

void Volume::remove_child(SynthItem *child)
{
    SynthItemCommand command;
    command.type = COMMAND::REMOVE_CHILD;
    command.item = child;
    command_buffer_.push(command);
}

void Volume::mute(bool mute)
{
    SynthItemCommand command;
    command.type = COMMAND::MUTE;
    command.bool_val = mute;
    command_buffer_.push(command);
}

void Volume::set_volume(double volume)
{
    SynthItemCommand command;
    command.type = COMMAND::PARAM;
    command.parameter = PARAMETER::VOLUME;
    command.doubles.push_back(volume);
    command_buffer_.push(command);
}

void Volume::set_volume_fixed(bool fixed)
{
    SynthItemCommand command;
    command.type = COMMAND::FIXED;
    command.parameter = PARAMETER::VOLUME;
    command.bool_val = fixed;
    command_buffer_.push(command);
}

void Volume::set_volume_indexes(std::vector<int> indexes)
{
    SynthItemCommand command;
    command.type = COMMAND::INDEXES;
    command.parameter = PARAMETER::VOLUME;
    command.ints.assign(indexes.begin(), indexes.end());
    command_buffer_.push(command);
}

void Volume::set_volume_scaled(bool scaled)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALED;
    command.parameter = PARAMETER::VOLUME;
    command.bool_val = scaled;
    command_buffer_.push(command);
}

void Volume::set_volume_scale_vals(double low, double high, double exp)
{
    SynthItemCommand command;
    command.type = COMMAND::SCALE_VALS;
    command.parameter = PARAMETER::VOLUME;
    command.doubles.push_back(low);
    command.doubles.push_back(high);
    command.doubles.push_back(exp);
    command_buffer_.push(command);
}

Frame Volume::process()
{
    Frame frame;

    if(!command_buffer_.empty())
    {
        retrieve_commands();
    }

    if(muted_)
    {
        return frame;
    }

    // no need to generate output if no input
    if(!inputs_.empty())
    {
        // get input
        Frame in_frame = visit_children(inputs_);
        in_frame /= inputs_.size();
        // generate volume value and apply to output frame
        float vol = calculate_volume_();
        frame = in_frame * vol;
    }

    // modulate
    if(!amods_.empty())
    {
        Frame am_frame = visit_children(amods_);
        frame *= am_frame;
    }

    return frame;
}

void Volume::step()
{
    for (unsigned int i = 0; i < amods_.size(); i++) {
        SynthItem *item = amods_[i];
        item->step();
    }
}

void Volume::retrieve_commands()
{
    while(command_buffer_.pop(&current_command_))
    {
        process_command(current_command_);
    }
}

void Volume::process_command(SynthItem::SynthItemCommand command)
{
    COMMAND type = command.type;

    switch (type) {
    case COMMAND::DATA:
        process_set_data(command.data, command.mins, command.maxes);
        break;
    case COMMAND::ADD_CHILD:
        process_add_child(command.item, command.parameter);
        break;
    case COMMAND::REMOVE_CHILD:
        process_remove_child(command.item);
        break;
    case COMMAND::ADD_PARENT:
        insert_item_unique(command.item, &parents_);
        break;
    case COMMAND::REMOVE_PARENT:
        erase_item(command.item, &parents_);
        break;
    case COMMAND::MUTE:
        muted_ = command.bool_val;
        break;
    case COMMAND::PARAM:
        process_set_param_value(command.doubles[0], command.parameter);
        break;
    case COMMAND::FIXED:
        process_set_param_fixed(command.bool_val, command.parameter);
        break;
    case COMMAND::INDEXES:
        process_set_param_indexes(command.ints, command.parameter);
        break;
    case COMMAND::SCALED:
        process_set_param_scaled(command.bool_val, command.parameter);
        break;
    case COMMAND::SCALE_VALS:
        process_set_param_scale_vals(command.doubles[0], command.doubles[1], command.doubles[2], command.parameter);
        break;
    case COMMAND::DELETE:
        process_delete_item();
        break;
    default:
        break;
    }
}

void Volume::process_add_child(SynthItem *child, SynthItem::PARAMETER parameter)
{
    switch (parameter){
    case PARAMETER::INPUT:
        insert_item_unique(child, &inputs_);
        child->add_parent(this);
        break;
    case PARAMETER::AMPLITUDE:
        insert_item_unique(child, &amods_);
        child->add_parent(this);
        break;
    default:
        break; //incompatible child type
    }
}

void Volume::process_remove_child(SynthItem *child)
{
    erase_item(child, &inputs_);
    erase_item(child, &amods_);
}

void Volume::process_delete_item()
{
    remove_as_child(this, parents_);
    remove_as_parent(this, inputs_);
    remove_as_parent(this, amods_);
    delete this;
}

void Volume::process_set_data(std::vector<double> *data, std::vector<double> *mins, std::vector<double> *maxes)
{
    data_ = data;
    mins_ = mins;
    maxes_ = maxes;
}

void Volume::process_set_param_value(double val, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::VOLUME)
    {
        volume_ = val;
    }
}

void Volume::process_set_param_fixed(bool fixed, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::VOLUME)
    {
        volume_fixed_ = fixed;
    }
}

void Volume::process_set_param_indexes(std::vector<int> indexes, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::VOLUME)
    {
        volume_indexes_ = indexes;
    }
}

void Volume::process_set_param_scaled(bool scaled, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::VOLUME)
    {
        volume_scaled_ = scaled;
    }
}

void Volume::process_set_param_scale_vals(double low, double high, double exp, SynthItem::PARAMETER param)
{
    if(param == PARAMETER::VOLUME)
    {
        volume_low_ = low;
        volume_high_ = high;
        volume_exponent_ = exp;
    }
}

float Volume::calculate_volume_()
{
    double volume = 0;
    if(volume_fixed_ || volume_indexes_.size() < 1) {
        volume = volume_;
    }
    else {
        int idx = volume_indexes_[0];
        volume = data_->at(idx);
        volume = scale(volume, mins_->at(idx), maxes_->at(idx), volume_low_, volume_high_, volume_exponent_);
    }
    return volume;
}

} // namespace son