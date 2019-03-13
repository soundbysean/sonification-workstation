#include "dataset.h"

namespace sow {

Dataset::Dataset(QObject *parent) : QObject (parent)
{
    height_ = 0;
    width_ = 0;
}

float Dataset::operator()(unsigned int x, unsigned int y)
{
    if ( x > height_ || y > width_ )
    {
        QString message = "Invalid dataset index: " + QString::number(x)
                + ", " + QString::number(y);
        throw InvalidArgumentException(message);
    }
    int idx = static_cast<int>((y * height_) + x);
    return data_[idx];
}

unsigned int Dataset::height() const
{
    return height_;
}

unsigned int Dataset::width() const
{
    return width_;
}

void Dataset::initialize(const QVector<float> data, const unsigned int height, const unsigned int width)
{
    if(static_cast<int>((height * width)) != data.size())
    {
        QString message = "Invalid dataset size. Rows x Cols != data size.";
        throw InvalidArgumentException(message);
    }

    data_.clear();
    data_ = data;
    height_ = height;
    width_ = width;
    calculateMinMax();
}

QVector<float> Dataset::getColumn(unsigned int col) const {

    if(col > width_)
    {
        QString message = "invalid dataset column requested: " + QString::number(col);
        throw InvalidArgumentException(message);
    }

    QVector<float> vec;
    for(unsigned int i = 0; i < height_; i++)
    {
        unsigned int idx = ((width_ * i) + col);
        vec.append(data_[static_cast<int>(idx)]);
    }
    return vec;
}

QVector<float> Dataset::getRow(unsigned int row) const {

    if(row > height_)
    {
        QString message = "invalid dataset row requested: " + QString::number(row);
        throw InvalidArgumentException(message);
    }

    QVector<float> vec;
    for(unsigned int i = 0; i < width_; i++)
    {
        unsigned int idx = ((width_ * row) + i);
        vec.append(data_[static_cast<int>(idx)]);
    }
    return vec;
}

void Dataset::calculateMinMax()
{
    float min = 0.0f;
    float max = 0.0f;
    mins_.clear();
    maxes_.clear();
    for(unsigned int i = 0; i < width_; i++)
    {
        for(unsigned int j = 0; j < height_; j++)
        {
            unsigned int idx = i * height_ + j;
            float value = data_[static_cast<int>(idx)];
            if(j == 0)
            {
                min = max = value;
            }
            else if(value < min)
            {
                min = value;
            }
            else if(value > max)
            {
                max = value;
            }
        }
        mins_.push_back(min);
        maxes_.push_back(max);
    }
}

void Dataset::clear()
{
    data_.clear();
    height_ = 0;
    width_ = 0;
}

}