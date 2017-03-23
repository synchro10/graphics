#include "myslider.h"



MySlider::MySlider(Qt::Orientation, QObject *parent)
{
    setOrientation(Qt::Horizontal);
}

void MySlider::setDoubleValue(double v)
{
    setValue((int)v*10);
}
