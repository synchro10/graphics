#ifndef EDGEWIDGET_H
#define EDGEWIDGET_H

#include <QtWidgets>

class EdgeWidget: public QWidget
{
public:
    EdgeWidget();
    QSpinBox* spinBoxA = nullptr;
    QSlider* sliderA = nullptr;
    QLabel* labelA = nullptr;

    QGridLayout *mainLayout = nullptr;

    void setup();
    int getValue(){ return sliderA->value();}
signals:

public slots:
};

#endif // EDGEWIDGET_H
