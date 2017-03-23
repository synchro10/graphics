#ifndef OPTIONS_H
#define OPTIONS_H

#include <QtWidgets>

class Options : public QDialog
{
public:
    Options(QObject *parent);

    QSpinBox* spinBoxM = nullptr;
    QSlider* sliderM = nullptr;
    QLabel* labelM = nullptr;
    QSpinBox* spinBoxN = nullptr;
    QSlider* sliderN = nullptr;
    QLabel* labelN = nullptr;
    QSpinBox* spinBoxC = nullptr;
    QSlider* sliderC = nullptr;
    QLabel* labelC = nullptr;

    QDoubleSpinBox* spinBoxLiveB = nullptr;
    QSlider*         sliderLiveB = nullptr;
    QLabel*           labelLiveB = nullptr;
    QDoubleSpinBox* spinBoxLiveE = nullptr;
    QSlider*         sliderLiveE = nullptr;
    QLabel*           labelLiveE = nullptr;
    QDoubleSpinBox* spinBoxBirthB = nullptr;
    QSlider*         sliderBirthB = nullptr;
    QLabel*           labelBirthB = nullptr;
    QDoubleSpinBox* spinBoxBirthE = nullptr;
    QSlider*         sliderBirthE = nullptr;
    QLabel*           labelBirthE = nullptr;
    QDoubleSpinBox* spinBoxFstI = nullptr;
    QSlider*         sliderFstI = nullptr;
    QLabel*           labelFstI = nullptr;
    QDoubleSpinBox* spinBoxSndI = nullptr;
    QSlider*         sliderSndI = nullptr;
    QLabel*           labelSndI = nullptr;


    QDialogButtonBox* button = nullptr;

    QGridLayout *mainLayout = nullptr;

    void setup();


};

#endif // OPTIONS_H
