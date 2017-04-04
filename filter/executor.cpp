#include "executor.h"
#include <QDebug>

Executor::Executor(QObject *parent) : QObject(parent)
{
    view = QSharedPointer<View>(new View());
    threadPool = new QThreadPool(this);
    threadPool->setMaxThreadCount(1);
    setup();
}

void Executor::blackWhiteFilter()
{
    ControlPanel* widget = new ControlPanel();
    view->setControl(widget);
    QImage* image = view->getImageB();
    Filter* filter = new BlackWhiteFilter();
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
}

void Executor::negativeFilter()
{
    ControlPanel* widget = new ControlPanel();
    view->setControl(widget);
    QImage* image = view->getImageB();
    Filter* filter = new NegativeFilter();
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
}

void Executor::ditheringFilter()
{
    std::cout << "В разработке" << std::endl;
}

void Executor::ditheringErrorFilter()
{
    std::cout << "В разработке" << std::endl;

}

void Executor::upscaleFilter()
{
    ControlPanel* widget = new ControlPanel();
    view->setControl(widget);
    QImage* image = view->getImageB();
    Filter* filter = new UpscaledFilter();
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
}

void Executor::rotateButton()
{
    RotateWidget* widget = new RotateWidget();
    connect(widget->sliderA, &QSlider::valueChanged, this, &Executor::rotateFilter);
    view->setControl(widget);
}

void Executor::rotateFilter(int value)
{
    QImage* image = view->getImageB();
    Filter* filter = new RotateFilter(value);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
}

void Executor::gammaFilter(int value)
{
    QImage* image = view->getImageB();
    Filter* filter = new GammaFilter((double)value/100);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
}

void Executor::edgeRobertButton()
{
    EdgeWidget* widget = new EdgeWidget();
    connect(widget->sliderA, &QSlider::valueChanged, this, &Executor::edgeRobertFilter);
    view->setControl(widget);
}

void Executor::gammaButton()
{
    GammaWidget* widget = new GammaWidget();
    connect(widget->sliderA, &QSlider::valueChanged, this, &Executor::gammaFilter);
    view->setControl(widget);
}

void Executor::edgeRobertFilter(int threshold)
{
    QImage* image = view->getImageB();
    Filter* filter = new EdgeRobertFilter(threshold);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);

}

void Executor::edgeSobelButton()
{
    EdgeWidget* widget = new EdgeWidget();
    connect(widget->sliderA, &QSlider::valueChanged, this, &Executor::edgeSobelFilter);
    view->setControl(widget);
}

void Executor::edgeSobelFilter(int threshold)
{
    QImage* image = view->getImageB();
    Filter* filter = new EdgeSobelFilter(threshold);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);

}

void Executor::embossFilter()
{
    ControlPanel* widget = new ControlPanel();
    view->setControl(widget);
    QImage* image = view->getImageB();
    Filter* filter = new EmbossFilter();
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);

}

void Executor::waterFilter()
{
    ControlPanel* widget = new ControlPanel();
    view->setControl(widget);
    QImage* image = view->getImageB();
    Filter* filter = new WaterFilter();
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
}

void Executor::blurFilter()
{
    ControlPanel* widget = new ControlPanel();
    view->setControl(widget);
    QImage* image = view->getImageB();
    Filter* filter = new BlurFilter();
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
}

void Executor::sharpenFilter()
{
    ControlPanel* widget = new ControlPanel();
    view->setControl(widget);
    QImage* image = view->getImageB();
    Filter* filter = new SharpenFilter();
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);

}

void Executor::setCImage(QImage *image)
{
    view->setImageC(image);
}

void Executor::setup()
{
    connect(view->blackWhiteAct, SIGNAL(triggered()),     this, SLOT(blackWhiteFilter    ()));
    connect(view->negativeAct, SIGNAL(triggered()),       this, SLOT(negativeFilter      ()));
    connect(view->ditheringAct     , SIGNAL(triggered()), this, SLOT(ditheringFilter     ()));
    connect(view->ditheringErrorAct, SIGNAL(triggered()), this, SLOT(ditheringErrorFilter()));
    connect(view->upscaleAct       , SIGNAL(triggered()), this, SLOT(upscaleFilter       ()));
    connect(view->rotateAct        , SIGNAL(triggered()), this, SLOT(rotateButton        ()));
    connect(view->gammaAct         , SIGNAL(triggered()), this, SLOT(gammaButton         ()));
    connect(view->edgeRobertAct    , SIGNAL(triggered()), this, SLOT(edgeRobertButton    ()));
    connect(view->edgeSobelAct     , SIGNAL(triggered()), this, SLOT(edgeSobelButton     ()));
    connect(view->embossAct        , SIGNAL(triggered()), this, SLOT(embossFilter        ()));
    connect(view->waterAct         , SIGNAL(triggered()), this, SLOT(waterFilter         ()));
    connect(view->blurAct          , SIGNAL(triggered()), this, SLOT(blurFilter          ()));
    connect(view->sharpenAct       , SIGNAL(triggered()), this, SLOT(sharpenFilter       ()));
}

void Executor::addTask(Filter *filter)
{
    threadPool->clear();
    threadPool->start(filter);
}
void Executor::execute()
{
    view->show();
}
