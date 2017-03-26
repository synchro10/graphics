#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QtWidgets>

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = 0);
    QSpinBox* spinBoxM = nullptr;
    QSlider* sliderM = nullptr;
    QLabel* labelM = nullptr;

    QSpinBox* spinBoxN = nullptr;
    QSlider* sliderN = nullptr;
    QLabel* labelN = nullptr;
    QSpinBox* spinBoxC = nullptr;
    QSlider* sliderC = nullptr;
    QLabel* labelC = nullptr;

    QPushButton* button = nullptr;

    QGridLayout *mainLayout = nullptr;

    void setup();
signals:

public slots:
};

#endif // CONTROLPANEL_H
