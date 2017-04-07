#ifndef ROTATEWIDGET_H
#define ROTATEWIDGET_H

#include <QtWidgets>

class RotateWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RotateWidget(QWidget *parent = 0);
    QSpinBox* spinBoxA = nullptr;
    QSlider* sliderA = nullptr;
    QLabel* labelA = nullptr;

    QGridLayout *mainLayout = nullptr;

    void setup();
    int getValue(){return sliderA->value();}
signals:

public slots:
};

#endif // ROTATEWIDGET_H
