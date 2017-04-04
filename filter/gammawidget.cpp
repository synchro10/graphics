#include "gammawidget.h"

GammaWidget::GammaWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QGridLayout;

    spinBoxA = new QDoubleSpinBox(this);
    sliderA = new QSlider(Qt::Horizontal , this);
    labelA = new QLabel(this);

    mainLayout->addWidget(labelA, 0, 0);
    mainLayout->addWidget(spinBoxA, 0, 1);
    mainLayout->addWidget(sliderA, 0, 2);

    setup();

    setLayout(mainLayout);
}

void GammaWidget::setup()
{
    setFixedSize(350*3, 200);
    labelA->setText("Gamma value");
    spinBoxA->setRange(0.01, 10.0);
    spinBoxA->setSingleStep(0.01);
    sliderA->setRange(1, 1000);

    connect(sliderA, &QSlider::valueChanged, [this] (int value){ spinBoxA->setValue((double)value/100); });
    connect(spinBoxA,  static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value){ sliderA->setValue((int)(value*100)); });
    spinBoxA->setValue(1.0);
    sliderA->setValue(100);
}
