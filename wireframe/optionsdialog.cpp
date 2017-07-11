#include "optionsdialog.h"

OptionsDialog::OptionsDialog(QObject *parent)
{
    setModal(true);
    setFixedSize(400,400);
    mainLayout = new QGridLayout;

    spinBoxK = new QSpinBox(this);
    sliderK = new QSlider(Qt::Horizontal , this);
    labelK = new QLabel(this);
    spinBoxM = new QSpinBox(this);
    sliderM = new QSlider(Qt::Horizontal , this);
    labelM = new QLabel(this);
    spinBoxN = new QSpinBox(this);
    sliderN = new QSlider(Qt::Horizontal , this);
    labelN = new QLabel(this);

    spinBoxA    = new QDoubleSpinBox(this);
    sliderA     = new QSlider(Qt::Horizontal , this);
    labelA      = new QLabel(this);
    spinBoxB    = new QDoubleSpinBox(this);
    sliderB     = new QSlider(Qt::Horizontal , this);
    labelB      = new QLabel(this);
    spinBoxC    = new QDoubleSpinBox(this);
    sliderC     = new QSlider(Qt::Horizontal , this);
    labelC      = new QLabel(this);
    spinBoxD    = new QDoubleSpinBox(this);
    sliderD     = new QSlider(Qt::Horizontal , this);
    labelD      = new QLabel(this);
    button      = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    mainLayout->addWidget(labelK,   2, 0);
    mainLayout->addWidget(spinBoxK, 2, 1);
    mainLayout->addWidget(sliderK,  2, 2);
    mainLayout->addWidget(labelM,   1, 0);
    mainLayout->addWidget(spinBoxM, 1, 1);
    mainLayout->addWidget(sliderM,  1, 2);
    mainLayout->addWidget(labelN,   0, 0);
    mainLayout->addWidget(spinBoxN, 0, 1);
    mainLayout->addWidget(sliderN,  0, 2);

    mainLayout->addWidget(labelA,   3, 0);
    mainLayout->addWidget(spinBoxA, 3, 1);
    mainLayout->addWidget(sliderA,  3, 2);
    mainLayout->addWidget(labelB,   4, 0);
    mainLayout->addWidget(spinBoxB, 4, 1);
    mainLayout->addWidget(sliderB,  4, 2);

    mainLayout->addWidget(labelC    , 5, 0);
    mainLayout->addWidget(spinBoxC  , 5, 1);
    mainLayout->addWidget(sliderC   , 5, 2);
    mainLayout->addWidget(labelD    , 6, 0);
    mainLayout->addWidget(spinBoxD  , 6, 1);
    mainLayout->addWidget(sliderD   , 6, 2);

    mainLayout->addWidget(button, 7, 1);

    setup();

    setLayout(mainLayout);
    update();
}

void OptionsDialog::setup()
{
    labelK->setText("k");
    labelM->setText("m");
    labelN->setText("n");
    labelA->setText("a");
    labelB->setText("b");
    labelC->setText("c");
    labelD->setText("d");

    spinBoxK->setRange(1, 15);
    spinBoxM->setRange(1, 15);
    spinBoxN->setRange(1, 15);
    sliderK->setRange(1, 15);
    sliderM->setRange(1, 15);
    sliderN->setRange(1, 15);

    spinBoxA->setRange(0.0, 1.0);
    spinBoxB->setRange(0.0, 1.0);
    spinBoxC->setRange(0.0, 6.3);
    spinBoxD->setRange(0.0, 6.3);
    spinBoxA-> setSingleStep(0.1);
    spinBoxB-> setSingleStep(0.1);
    spinBoxC-> setSingleStep(0.01);
    spinBoxD-> setSingleStep(0.01);

    sliderA->setRange(0, 10);
    sliderB->setRange(0, 10);
    sliderC->setRange(0, 63);
    sliderD->setRange(0, 63);

    connect(sliderK, SIGNAL(valueChanged(int)), spinBoxK, SLOT(setValue(int)));
    connect(spinBoxK, SIGNAL(valueChanged(int)), sliderK, SLOT(setValue(int)));

    connect(sliderM, SIGNAL(valueChanged(int)), spinBoxM, SLOT(setValue(int)));
    connect(spinBoxM, SIGNAL(valueChanged(int)), sliderM, SLOT(setValue(int)));

    connect(sliderN, SIGNAL(valueChanged(int)), spinBoxN, SLOT(setValue(int)));
    connect(spinBoxN, SIGNAL(valueChanged(int)), sliderN, SLOT(setValue(int)));

    connect(sliderA, &QSlider::valueChanged, [this] (int value){ spinBoxA->setValue((double)value/10); });
    connect(spinBoxA,  static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value){ sliderA->setValue((int)(value*10)); });

    connect(sliderB, &QSlider::valueChanged, [this] (int value){ spinBoxB->setValue((double)value/10); });
    connect(spinBoxB,  static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value){ sliderB->setValue((int)(value*10)); });

    connect(sliderC, &QSlider::valueChanged, [this] (int value){ spinBoxC->setValue((double)value/10); });
    connect(spinBoxC,  static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value){ sliderC->setValue((int)(value*10)); });

    connect(sliderD, &QSlider::valueChanged, [this] (int value){ spinBoxD->setValue((double)value/10); });
    connect(spinBoxD,  static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [this](double value){ sliderD->setValue((int)(value*10)); });

    connect(button, SIGNAL(rejected()), this, SLOT(close()));
    connect(button, SIGNAL(accepted()), this, SLOT(finish()));
}

void OptionsDialog::init(const Settings &settings)
{
    this->settings = settings;
    update();
}

void OptionsDialog::update()
{
    spinBoxK->setValue(settings.k);
    spinBoxA->setValue(settings.a);
    spinBoxB->setValue(settings.b);
    spinBoxC->setValue(settings.c);
    spinBoxD->setValue(settings.d);
    spinBoxM->setValue(settings.m);
    spinBoxN->setValue(settings.n);
}

void OptionsDialog::setSettings(Settings settings)
{
    this->settings = settings;
    update();
}

void OptionsDialog::finish()
{
    settings = Settings(spinBoxN->value(), spinBoxM->value(), spinBoxK->value(),
                              spinBoxA->value(), spinBoxB->value(),
                              spinBoxC->value(), spinBoxD->value());
    emit changeSettings(settings);
    this->close();
}
