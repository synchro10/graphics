#include "edgewidget.h"

EdgeWidget::EdgeWidget()
{
    mainLayout = new QGridLayout;

    spinBoxA = new QSpinBox(this);
    sliderA = new QSlider(Qt::Horizontal , this);
    labelA = new QLabel(this);

    mainLayout->addWidget(labelA, 0, 0);
    mainLayout->addWidget(spinBoxA, 0, 1);
    mainLayout->addWidget(sliderA, 0, 2);

    setup();

    setLayout(mainLayout);
}

void EdgeWidget::setup()
{
    setFixedSize(350*3, 200);
    labelA->setText("Threshold");
    spinBoxA->setRange(0, 255);
    sliderA->setRange(0, 255);

    connect(sliderA, SIGNAL(valueChanged(int)), spinBoxA, SLOT(setValue(int)));
    connect(spinBoxA, SIGNAL(valueChanged(int)), sliderA, SLOT(setValue(int)));
    spinBoxA->setValue(20);
}

