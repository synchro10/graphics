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

    QPushButton* button = nullptr;

    QGridLayout *mainLayout = nullptr;

    void setup();
signals:

public slots:
};

#endif // ROTATEWIDGET_H
