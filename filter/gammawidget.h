#ifndef GAMMAWIDGET_H
#define GAMMAWIDGET_H

#include <QtWidgets>

class GammaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GammaWidget(QWidget *parent = 0);
    QDoubleSpinBox* spinBoxA = nullptr;
    QSlider* sliderA = nullptr;
    QLabel* labelA = nullptr;

    QGridLayout *mainLayout = nullptr;

    void setup();
    double getValue(){return spinBoxA->value();}
signals:

public slots:
};

#endif // GAMMAWIDGET_H
