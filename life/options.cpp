#include "options.h"

Options::Options(QObject *parent)
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

    spinBoxLiveB    = new QDoubleSpinBox(this);
    sliderLiveB     = new QSlider(Qt::Horizontal , this);
    labelLiveB      = new QLabel(this);
    spinBoxLiveE    = new QDoubleSpinBox(this);
    sliderLiveE     = new QSlider(Qt::Horizontal , this);
    labelLiveE      = new QLabel(this);
    spinBoxBirthB   = new QDoubleSpinBox(this);
    sliderBirthB    = new QSlider(Qt::Horizontal , this);
    labelBirthB     = new QLabel(this);
    spinBoxBirthE   = new QDoubleSpinBox(this);
    sliderBirthE    = new QSlider(Qt::Horizontal , this);
    labelBirthE     = new QLabel(this);
    spinBoxFstI     = new QDoubleSpinBox(this);
    sliderFstI      = new QSlider(Qt::Horizontal , this);
    labelFstI       = new QLabel(this);
    spinBoxSndI     = new QDoubleSpinBox(this);
    sliderSndI      = new QSlider(Qt::Horizontal , this);
    labelSndI       = new QLabel(this);
    button          = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    mainLayout->addWidget(labelM, 0, 0);
    mainLayout->addWidget(spinBoxM, 0, 1);
    mainLayout->addWidget(sliderM, 0, 2);
    mainLayout->addWidget(labelN, 1, 0);
    mainLayout->addWidget(spinBoxN, 1, 1);
    mainLayout->addWidget(sliderN, 1, 2);
    mainLayout->addWidget(labelC, 2, 0);
    mainLayout->addWidget(spinBoxC, 2, 1);
    mainLayout->addWidget(sliderC, 2, 2);

    mainLayout->addWidget(labelLiveB, 3, 0);
    mainLayout->addWidget(spinBoxLiveB, 3, 1);
    mainLayout->addWidget(sliderLiveB, 3, 2);
    mainLayout->addWidget(labelLiveE, 3, 3);
    mainLayout->addWidget(spinBoxLiveE, 3, 4);
    mainLayout->addWidget(sliderLiveE, 3, 5);

    mainLayout->addWidget(spinBoxBirthB  , 4, 2 - 1);
    mainLayout->addWidget(sliderBirthB   , 4, 3 - 1);
    mainLayout->addWidget(labelBirthB    , 4, 1 - 1);
    mainLayout->addWidget(spinBoxBirthE  , 4, 5 - 1);
    mainLayout->addWidget(sliderBirthE   , 4, 6 - 1);
    mainLayout->addWidget(labelBirthE    , 4, 4 - 1);

    mainLayout->addWidget(spinBoxFstI  , 5, 2 - 1);
    mainLayout->addWidget(sliderFstI   , 5, 3 - 1);
    mainLayout->addWidget(labelFstI    , 5, 1 - 1);
    mainLayout->addWidget(spinBoxSndI  , 5, 5 - 1);
    mainLayout->addWidget(sliderSndI   , 5, 6 - 1);
    mainLayout->addWidget(labelSndI    , 5, 4 - 1);

    mainLayout->addWidget(button, 6, 3);

    setup();

    setLayout(mainLayout);
}

void Options::setup()
{
    labelM->setText("M");
    labelN->setText("N");
    labelC->setText("Cell Size");
    labelBirthB->setText("Birth begin");
    labelBirthE->setText("Birth end");
    labelLiveB->setText("Live begin");
    labelLiveE->setText("Live end");
    labelFstI->setText("FST impact");
    labelSndI->setText("SND impact");

    spinBoxM->setRange(1,200);
    spinBoxN->setRange(1,200);
    spinBoxC->setRange(4, 66);
    sliderM->setRange(1,200);
    sliderN->setRange(1,200);
    sliderC->setRange(4, 66);

    spinBoxLiveB->setRange(0.1, 5.0);
    spinBoxLiveE->setRange(0.1, 5.0);
    spinBoxBirthB->setRange(0.1, 5.0);
    spinBoxBirthE->setRange(0.1, 5.0);
    spinBoxFstI->setRange(0.1, 5.0);
    spinBoxSndI->setRange(0.1, 5.0);
    spinBoxLiveB->  setSingleStep(0.1);
    spinBoxLiveE->  setSingleStep(0.1);
    spinBoxBirthB-> setSingleStep(0.1);
    spinBoxBirthE-> setSingleStep(0.1);
    spinBoxFstI->   setSingleStep(0.1);
    spinBoxSndI->   setSingleStep(0.1);

    sliderLiveB->setRange   (1, 50);
    sliderLiveE->setRange   (1, 50);
    sliderBirthB->setRange  (1, 50);
    sliderBirthE->setRange  (1, 50);
    sliderFstI->setRange    (1, 50);
    sliderSndI->setRange    (1, 50);

    connect(sliderM, SIGNAL(valueChanged(int)), spinBoxM, SLOT(setValue(int)));
    connect(spinBoxM, SIGNAL(valueChanged(int)), sliderM, SLOT(setValue(int)));
    connect(sliderN, SIGNAL(valueChanged(int)), spinBoxN, SLOT(setValue(int)));
    connect(spinBoxN, SIGNAL(valueChanged(int)), sliderN, SLOT(setValue(int)));
    connect(sliderC, SIGNAL(valueChanged(int)), spinBoxC, SLOT(setValue(int)));
    connect(spinBoxC, SIGNAL(valueChanged(int)), sliderC, SLOT(setValue(int)));

    connect(sliderLiveB, &QSlider::valueChanged, [this] (int value){ spinBoxLiveB->setValue((double)value/10); });
    connect(spinBoxLiveB,  static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value){ sliderLiveB->setValue((int)(value*10)); });

    connect(sliderLiveE, &QSlider::valueChanged, [this] (int value){ spinBoxLiveE->setValue((double)value/10); });
    connect(spinBoxLiveE,  static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value){ sliderLiveE->setValue((int)(value*10)); });

    connect(sliderBirthB, &QSlider::valueChanged, [this] (int value){ spinBoxBirthB->setValue((double)value/10); });
    connect(spinBoxBirthB,  static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value){ sliderBirthB->setValue((int)(value*10)); });

    connect(sliderBirthE, &QSlider::valueChanged, [this] (int value){ spinBoxBirthE->setValue((double)value/10); });
    connect(spinBoxBirthE,  static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value){ sliderBirthE->setValue((int)(value*10)); });

    connect(sliderFstI, &QSlider::valueChanged, [this] (int value){ spinBoxFstI->setValue((double)value/10); });
    connect(spinBoxFstI,  static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value){ sliderFstI->setValue((int)(value*10)); });

    connect(sliderSndI, &QSlider::valueChanged, [this] (int value){ spinBoxSndI->setValue((double)value/10); });
    connect(spinBoxSndI,  static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value){ sliderSndI->setValue((int)(value*10)); });

    connect(button, SIGNAL(rejected()), this, SLOT(close()));
}

