#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <QSlider>

class MySlider : public QSlider
{
public:
    MySlider(Qt::Orientation, QObject *parent);
public slots:
    void setDoubleValue(double v);
};

#endif // MYSLIDER_H
