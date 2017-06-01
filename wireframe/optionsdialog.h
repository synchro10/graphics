#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QtWidgets>
#include "settings.h"

class OptionsDialog : public QDialog
{
    Q_OBJECT
public:
    OptionsDialog(QObject *parent);

    QSpinBox* spinBoxM = nullptr;
    QSlider* sliderM = nullptr;
    QLabel* labelM = nullptr;
    QSpinBox* spinBoxN = nullptr;
    QSlider* sliderN = nullptr;
    QLabel* labelN = nullptr;
    QSpinBox* spinBoxK = nullptr;
    QSlider* sliderK = nullptr;
    QLabel* labelK = nullptr;

    QDoubleSpinBox* spinBoxA = nullptr;
    QSlider*         sliderA = nullptr;
    QLabel*           labelA = nullptr;
    QDoubleSpinBox* spinBoxB = nullptr;
    QSlider*         sliderB = nullptr;
    QLabel*           labelB = nullptr;
    QDoubleSpinBox* spinBoxC = nullptr;
    QSlider*         sliderC = nullptr;
    QLabel*           labelC = nullptr;
    QDoubleSpinBox* spinBoxD = nullptr;
    QSlider*         sliderD = nullptr;
    QLabel*           labelD = nullptr;

    QDialogButtonBox* button = nullptr;

    QGridLayout *mainLayout = nullptr;

    void setup();
    void init(const Settings& settings);
    void update();
signals:
    void changeSettings(Settings settings);

public slots:
    void setSettings(Settings settings);
    void finish();
private:
    Settings settings = Settings();
};

#endif // OPTIONSDIALOG_H
