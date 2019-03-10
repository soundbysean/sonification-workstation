#ifndef PARAMETER_H
#define PARAMETER_H

#include <QObject>
#include "sowenums.h"
#include "ringbuffer.h"
#include "commands.h"

namespace sow {

class Parameter : public QObject
{
    Q_OBJECT
public:
    explicit Parameter(QObject *parent = nullptr);


private:

    // Backing variables, used by sow
    SowEnums::PARAMETER type_;
    QString name_;
    float value_;
    bool fixed_;
    bool scaled_;
    float scaleLo_;
    float scaleHi_;
    float scaleExp_;
    QString map_;

    RingBuffer<ParameterCommand> commandBuffer_;

    void ProcessCommand(ParameterCommand c);

signals:

public slots:
    void onParameterChanged(ParameterCommand command);

};

} // namespace sow

#endif // PARAMETER_H
