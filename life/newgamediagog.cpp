#include "newgamediagog.h"

NewGameDiagog::NewGameDiagog(QObject *parent)
{
    setModal(true);
    mainLayout = new QGridLayout;

    spinBoxM = new QSpinBox(this);
    sliderM = new QSlider(Qt::Horizontal , this);
    labelM = new QLabel(this);
    spinBoxN = new QSpinBox(this);
    sliderN = new QSlider(Qt::Horizontal , this);
    labelN = new QLabel(this);
    spinBoxC = new QSpinBox(this);
    sliderC = new QSlider(Qt::Horizontal , this);
    labelC = new QLabel(this);
    button = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    mainLayout->addWidget(labelM, 0, 0);
    mainLayout->addWidget(spinBoxM, 0, 1);
    mainLayout->addWidget(sliderM, 0, 2);
    mainLayout->addWidget(labelN, 1, 0);
    mainLayout->addWidget(spinBoxN, 1, 1);
    mainLayout->addWidget(sliderN, 1, 2);
    mainLayout->addWidget(labelC, 2, 0);
    mainLayout->addWidget(spinBoxC, 2, 1);
    mainLayout->addWidget(sliderC, 2, 2);
    mainLayout->addWidget(button, 3, 1);

    setup();

    setLayout(mainLayout);
}

void NewGameDiagog::setup()
{
    labelM->setText("M");
    labelN->setText("N");
    labelC->setText("Cell Size");
    spinBoxM->setMaximum(200);
    spinBoxM->setMinimum(1);
    spinBoxN->setMaximum(200);
    spinBoxN->setMinimum(1);
    spinBoxC->setRange(4, 66);
    sliderM->setMaximum(200);
    sliderM->setMinimum(1);
    sliderN->setMaximum(200);
    sliderN->setMinimum(1);
    sliderC->setRange(4, 66);

    connect(sliderM, SIGNAL(valueChanged(int)), spinBoxM, SLOT(setValue(int)));
    connect(spinBoxM, SIGNAL(valueChanged(int)), sliderM, SLOT(setValue(int)));
    connect(sliderN, SIGNAL(valueChanged(int)), spinBoxN, SLOT(setValue(int)));
    connect(spinBoxN, SIGNAL(valueChanged(int)), sliderN, SLOT(setValue(int)));
    connect(sliderC, SIGNAL(valueChanged(int)), spinBoxC, SLOT(setValue(int)));
    connect(spinBoxC, SIGNAL(valueChanged(int)), sliderC, SLOT(setValue(int)));

    connect(button, SIGNAL(rejected()), this, SLOT(close()));

}
