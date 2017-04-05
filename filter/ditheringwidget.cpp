#include "ditheringwidget.h"

DitheringWidget::DitheringWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QGridLayout;

    spinBoxRed = new QSpinBox(this);
    sliderRed = new QSlider(Qt::Horizontal , this);
    labelRed = new QLabel(this);

    mainLayout->addWidget(labelRed, 0, 0);
    mainLayout->addWidget(spinBoxRed, 0, 1);
    mainLayout->addWidget(sliderRed, 0, 2);

    spinBoxGreen= new QSpinBox(this);
    sliderGreen = new QSlider(Qt::Horizontal , this);
    labelGreen = new QLabel(this);

    mainLayout->addWidget(labelGreen, 1, 0);
    mainLayout->addWidget(spinBoxGreen, 1, 1);
    mainLayout->addWidget(sliderGreen, 1, 2);

    spinBoxBlue = new QSpinBox(this);
    sliderBlue = new QSlider(Qt::Horizontal , this);
    labelBlue = new QLabel(this);

    mainLayout->addWidget(labelBlue, 2, 0);
    mainLayout->addWidget(spinBoxBlue, 2, 1);
    mainLayout->addWidget(sliderBlue, 2, 2);

    setup();

    setLayout(mainLayout);
}

void DitheringWidget::setup()
{
    setFixedSize(350*3, 200);

    labelRed->setText("Red");
    spinBoxRed->setRange(2, 24);
    sliderRed->setRange(2, 24);
    connect(sliderRed, SIGNAL(valueChanged(int)), spinBoxRed, SLOT(setValue(int)));
    connect(spinBoxRed, SIGNAL(valueChanged(int)), sliderRed, SLOT(setValue(int)));
    spinBoxRed->setValue(2);

    labelGreen->setText("Green");
    spinBoxGreen->setRange(2, 24);
    sliderGreen->setRange(2, 24);
    connect(sliderGreen, SIGNAL(valueChanged(int)), spinBoxGreen, SLOT(setValue(int)));
    connect(spinBoxGreen, SIGNAL(valueChanged(int)), sliderGreen, SLOT(setValue(int)));
    spinBoxGreen->setValue(2);

    labelBlue->setText("Blue");
    spinBoxBlue->setRange(2, 24);
    sliderBlue->setRange(2, 24);
    connect(sliderBlue, SIGNAL(valueChanged(int)), spinBoxBlue, SLOT(setValue(int)));
    connect(spinBoxBlue, SIGNAL(valueChanged(int)), sliderBlue, SLOT(setValue(int)));
    spinBoxBlue->setValue(2);

}
