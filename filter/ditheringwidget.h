#ifndef DITHERINGWIDGET_H
#define DITHERINGWIDGET_H

#include <QtWidgets>

class DitheringWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DitheringWidget(QWidget *parent = 0);
    QSpinBox* spinBoxRed = nullptr;
    QSlider* sliderRed = nullptr;
    QLabel* labelRed = nullptr;
    QSpinBox* spinBoxGreen = nullptr;
    QSlider* sliderGreen = nullptr;
    QLabel* labelGreen = nullptr;
    QSpinBox* spinBoxBlue = nullptr;
    QSlider* sliderBlue = nullptr;
    QLabel* labelBlue = nullptr;

    QGridLayout *mainLayout = nullptr;

    void setup();
signals:

public slots:
};

#endif // DITHERINGWIDGET_H
