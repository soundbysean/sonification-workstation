#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QObject>
#include "enums.h"
#include "dataset.h"
#include "ringbuffer.h"

namespace sow {

class DataProcessor : public QObject
{
    Q_OBJECT
public:
    explicit DataProcessor(QObject *parent = nullptr, Dataset* dataset = nullptr, uint size = 512);

    // Get the next value
    float getValue(uint row, uint col);

    ENUMS::PROCESSING_TYPE processingType();
    void setProcessingType(ENUMS::PROCESSING_TYPE type);
    uint n() const;
    void setN(float n);
    void flush();

private:

    Dataset* dataset_;
    RingBuffer<float>* buffer_;
    ENUMS::PROCESSING_TYPE processingType_ = ENUMS::PROCESSING_TYPE::NONE;
    uint n_ = 2;
    float emaPrevious_;
    bool initialized_ = false;

    float sma(unsigned int row, unsigned int col);
    float ema(int row, int col);

signals:

public slots:



};

} // Namespace sow.

#endif // DATAPROCESSOR_H
