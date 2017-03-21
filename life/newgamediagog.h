#ifndef NEWGAMEDIAGOG_H
#define NEWGAMEDIAGOG_H

#include <QDialog>
#include <QtWidgets>

class NewGameDiagog : public QDialog
{
    Q_OBJECT
public:
    explicit NewGameDiagog(QObject *parent = 0);
    QSpinBox* spinBoxM = nullptr;
    QSlider* sliderM = nullptr;
    QLabel* labelM = nullptr;

    QSpinBox* spinBoxN = nullptr;
    QSlider* sliderN = nullptr;
    QLabel* labelN = nullptr;
    QSpinBox* spinBoxC = nullptr;
    QSlider* sliderC = nullptr;
    QLabel* labelC = nullptr;

    QDialogButtonBox* button = nullptr;

    QGridLayout *mainLayout = nullptr;

    void setup();


signals:

public slots:
};

#endif // NEWGAMEDIAGOG_H
