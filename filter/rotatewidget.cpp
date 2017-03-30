#include "rotatewidget.h"

RotateWidget::RotateWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QGridLayout;

    spinBoxA = new QSpinBox(this);
    sliderA = new QSlider(Qt::Horizontal , this);
    labelA = new QLabel(this);

    button = new QPushButton("Apply", this);

    mainLayout->addWidget(labelA, 0, 0);
    mainLayout->addWidget(spinBoxA, 0, 1);
    mainLayout->addWidget(sliderA, 0, 2);

    mainLayout->addWidget(button, 1, 1);

    setup();

    setLayout(mainLayout);
}

void RotateWidget::setup()
{
    setFixedSize(350*3, 200);
    labelA->setText("Angle");
    spinBoxA->setRange(-180, 180);
    sliderA->setRange(-180, 180);

    connect(sliderA, SIGNAL(valueChanged(int)), spinBoxA, SLOT(setValue(int)));
    connect(spinBoxA, SIGNAL(valueChanged(int)), sliderA, SLOT(setValue(int)));
    spinBoxA->setValue(0);
    sliderA->setValue(0);
}
