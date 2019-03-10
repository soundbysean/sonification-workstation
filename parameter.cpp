#include "parameter.h"
#include <QString>
#include <QDebug>

namespace sow {

Parameter::Parameter(QObject *parent) : QObject(parent)
{

}

void Parameter::connectInterface(ParameterInterface *interface)
{
    connect(interface, &ParameterInterface::iParameterChanged,
            this, &Parameter::onParameterChanged);
    connect(interface, &ParameterInterface::iMapChanged,
            this, &Parameter::onMapChanged);
}

void Parameter::processCommand(sow::ParameterCommand cmd)
{
    SowEnums::SUB_PARAMETER subParam = cmd.subParam;

    switch (subParam) {
    case SowEnums::SUB_PARAMETER::VALUE:
        value_ = cmd.value;
        break;
    case SowEnums::SUB_PARAMETER::FIXED:
        fixed_ = (cmd.value != 0.0f);
        break;
    case SowEnums::SUB_PARAMETER::SCALED:
        scaled_ = (cmd.value != 0.0f);
        break;
    case SowEnums::SUB_PARAMETER::SCALE_LO:
        scaleLo_ = cmd.value;
        break;
    case SowEnums::SUB_PARAMETER::SCALE_HI:
        scaleHi_ = cmd.value;
        break;
    case SowEnums::SUB_PARAMETER::SCALE_EXP:
        scaleExp_ = cmd.value;
        break;
    case SowEnums::SUB_PARAMETER::MAP:
        map_ = cmd.map;
        break;
    }

    qDebug() << "Parameter.cpp: " + QString::number((int)subParam) + " " + QString::number(cmd.value) + " " + cmd.map;
}

void Parameter::onParameterChanged(const SowEnums::SUB_PARAMETER subParam, const float value)
{
    ParameterCommand cmd;
    cmd.subParam = subParam;
    cmd.value = value;
    commandBuffer_.push(cmd);
}

void Parameter::onMapChanged(const QString map)
{
    ParameterCommand cmd;
    cmd.subParam = SowEnums::SUB_PARAMETER::MAP;
    cmd.map = map;
    commandBuffer_.push(cmd);
}

} // namespace sow
