#ifndef OPTIONS_H
#define OPTIONS_H

#include <QtWidgets>

class Options{
public:
    int k = 10;
    int m = 10;
    double a = 0.0;
    double b = 1.0;
    double c = 0.0;
    double d = 1.0;
    Options(int, int, double, double, double, double);
};

class OptionsDialog : public QDialog
{
    Q_OBJECT
public:
    OptionsDialog(QObject *parent);

    QSpinBox* spinBoxK = nullptr;
    QSlider* sliderK = nullptr;
    QLabel* labelK = nullptr;
    QSpinBox* spinBoxM = nullptr;
    QSlider* sliderM = nullptr;
    QLabel* labelM = nullptr;

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
    void init(const Options& options);

signals:
    void finished(const Options options);
private slots:
    void finish();
};

#endif // OPTIONS_H
