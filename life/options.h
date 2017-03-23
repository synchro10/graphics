#ifndef OPTIONS_H
#define OPTIONS_H

#include <QtWidgets>
#include "mydoublespinbox.h"
#include "myslider.h"

class Options : public QDialog
{
public:
    Options(QObject *parent);

    QSpinBox* spinBoxM = nullptr;
    MySlider* sliderM = nullptr;
    QLabel* labelM = nullptr;
    QSpinBox* spinBoxN = nullptr;
    MySlider* sliderN = nullptr;
    QLabel* labelN = nullptr;
    QSpinBox* spinBoxC = nullptr;
    MySlider* sliderC = nullptr;
    QLabel* labelC = nullptr;

    MyDoubleSpinBox* spinBoxLiveB = nullptr;
    MySlider*         sliderLiveB = nullptr;
    QLabel*           labelLiveB = nullptr;
    MyDoubleSpinBox* spinBoxLiveE = nullptr;
    MySlider*         sliderLiveE = nullptr;
    QLabel*           labelLiveE = nullptr;
    MyDoubleSpinBox* spinBoxBirthB = nullptr;
    MySlider*         sliderBirthB = nullptr;
    QLabel*           labelBirthB = nullptr;
    MyDoubleSpinBox* spinBoxBirthE = nullptr;
    MySlider*         sliderBirthE = nullptr;
    QLabel*           labelBirthE = nullptr;
    MyDoubleSpinBox* spinBoxFstI = nullptr;
    MySlider*         sliderFstI = nullptr;
    QLabel*           labelFstI = nullptr;
    MyDoubleSpinBox* spinBoxSndI = nullptr;
    MySlider*         sliderSndI = nullptr;
    QLabel*           labelSndI = nullptr;


    QDialogButtonBox* button = nullptr;

    QGridLayout *mainLayout = nullptr;

    void setup();


};

#endif // OPTIONS_H
