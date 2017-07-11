#include "options.h"

OptionsDialog::OptionsDialog(QObject *parent)
{
    setModal(true);
    setFixedSize(300,300);
    mainLayout = new QGridLayout;

    spinBoxK = new QSpinBox(this);
    sliderK = new QSlider(Qt::Horizontal , this);
    labelK = new QLabel(this);
    spinBoxM = new QSpinBox(this);
    sliderM = new QSlider(Qt::Horizontal , this);
    labelM = new QLabel(this);

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

    mainLayout->addWidget(labelK, 0, 0);
    mainLayout->addWidget(spinBoxK, 0, 1);
    mainLayout->addWidget(sliderK, 0, 2);
    mainLayout->addWidget(labelM, 1, 0);
    mainLayout->addWidget(spinBoxM, 1, 1);
    mainLayout->addWidget(sliderM, 1, 2);

    mainLayout->addWidget(labelA,   2, 0);
    mainLayout->addWidget(spinBoxA, 2, 1);
    mainLayout->addWidget(sliderA,  2, 2);
    mainLayout->addWidget(labelB,   3, 0);
    mainLayout->addWidget(spinBoxB, 3, 1);
    mainLayout->addWidget(sliderB,  3, 2);

    mainLayout->addWidget(labelC    , 4, 0);
    mainLayout->addWidget(spinBoxC  , 4, 1);
    mainLayout->addWidget(sliderC   , 4, 2);
    mainLayout->addWidget(labelD    , 5, 0);
    mainLayout->addWidget(spinBoxD  , 5, 1);
    mainLayout->addWidget(sliderD   , 5, 2);

    mainLayout->addWidget(button, 6, 1);

    setup();

    setLayout(mainLayout);
}

void OptionsDialog::setup()
{
    labelK->setText("m");
    labelM->setText("k");
    labelA->setText("a");
    labelB->setText("b");
    labelC->setText("c");
    labelD->setText("d");

    spinBoxK->setRange(2,100);
    spinBoxM->setRange(2,100);
    sliderK-> setRange(2,100);
    sliderM-> setRange(2,100);

    spinBoxA->setRange(-10.0, 10.0);
    spinBoxB->setRange(-10.0, 10.0);
    spinBoxC->setRange(-10.0, 10.0);
    spinBoxD->setRange(-10.0, 10.0);
    spinBoxA-> setSingleStep(0.1);
    spinBoxB-> setSingleStep(0.1);
    spinBoxC-> setSingleStep(0.1);
    spinBoxD-> setSingleStep(0.1);

    sliderA->setRange(-100, 100);
    sliderB->setRange(-100, 100);
    sliderC->setRange(-100, 100);
    sliderD->setRange(-100, 100);

    connect(sliderK, SIGNAL(valueChanged(int)), spinBoxK, SLOT(setValue(int)));
    connect(spinBoxK, SIGNAL(valueChanged(int)), sliderK, SLOT(setValue(int)));

    connect(sliderM, SIGNAL(valueChanged(int)), spinBoxM, SLOT(setValue(int)));
    connect(spinBoxM, SIGNAL(valueChanged(int)), sliderM, SLOT(setValue(int)));

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

void OptionsDialog::init(const Options &options)
{
    spinBoxK->setValue(options.k);
    spinBoxM->setValue(options.m);
    spinBoxA->setValue(options.a);
    spinBoxB->setValue(options.b);
    spinBoxC->setValue(options.c);
    spinBoxD->setValue(options.d);
}

void OptionsDialog::finish()
{
    emit(finished(Options(sliderK->value(), sliderM->value(), spinBoxA->value(),
                          spinBoxB->value(), spinBoxC->value(), spinBoxD->value())));
}

Options::Options(int k, int m, double a, double b, double c, double d)
{
    this->a = a;
    this->b = b;
    this->c = c;
    this->d = d;
    this->k = k;
    this->m = m;
}
