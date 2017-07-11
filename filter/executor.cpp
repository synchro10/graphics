#include "executor.h"
#include <QDebug>

Executor::Executor(QObject *parent) : QObject(parent)
{
    view = QSharedPointer<View>(new View());
    zoneA = view->getZoneA();
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
    lastFilter = &Executor::blackWhiteFilter;
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
    lastFilter = &Executor::negativeFilter;
}

void Executor::ditheringFilter()
{
    ControlPanel* widget = new ControlPanel();
    view->setControl(widget);
    QImage* image = view->getImageB();
    Filter* filter = new DitheringFilter();
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
    lastFilter = &Executor::ditheringFilter;
}

void Executor::ditheringFloydFilter()
{
    DitheringWidget* widget = dynamic_cast<DitheringWidget*>(controlWidget);
    int red = widget->sliderRed->value();
    int green = widget->sliderGreen->value();
    int blue = widget->sliderBlue->value();
    QImage* image = view->getImageB();
    Filter* filter = new DithringFloydFilter(red, green, blue);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
    lastFilter = &Executor::ditheringFloydFilter;
}

void Executor::ditheringFloydButton()
{
    DitheringWidget* widget = new DitheringWidget();
    connect(widget->sliderRed, &QSlider::valueChanged, this, &Executor::ditheringFloydFilter);
    connect(widget->sliderGreen, &QSlider::valueChanged, this, &Executor::ditheringFloydFilter);
    connect(widget->sliderBlue, &QSlider::valueChanged, this, &Executor::ditheringFloydFilter);
    view->setControl(widget);
    controlWidget = widget;
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
    lastFilter = &Executor::upscaleFilter;
}

void Executor::rotateButton()
{
    RotateWidget* widget = new RotateWidget();
    connect(widget->sliderA, &QSlider::valueChanged, this, &Executor::rotateFilter);
    view->setControl(widget);
    controlWidget = widget;
}

void Executor::rotateFilter(int value)
{
    QImage* image = view->getImageB();
    Filter* filter = new RotateFilter(value);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
    lastFilter = &Executor::rotateFilter1;
}

void Executor::rotateFilter1()
{
    RotateWidget* widget = dynamic_cast<RotateWidget*>(controlWidget);
    int value = widget->getValue();
    QImage* image = view->getImageB();
    Filter* filter = new RotateFilter(value);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
    lastFilter = &Executor::rotateFilter1;
}

void Executor::gammaFilter(int value)
{
    QImage* image = view->getImageB();
    Filter* filter = new GammaFilter((double)value/100);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
    lastFilter = &Executor::gammaFilter1;
}

void Executor::gammaFilter1()
{
    GammaWidget* widget = dynamic_cast<GammaWidget*>(controlWidget);
    double value = widget->getValue();
    QImage* image = view->getImageB();
    Filter* filter = new GammaFilter(value);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
    lastFilter = &Executor::gammaFilter1;
}

void Executor::edgeRobertButton()
{
    EdgeWidget* widget = new EdgeWidget();
    connect(widget->sliderA, &QSlider::valueChanged, this, &Executor::edgeRobertFilter);
    view->setControl(widget);
    controlWidget = widget;
}

void Executor::gammaButton()
{
    GammaWidget* widget = new GammaWidget();
    connect(widget->sliderA, &QSlider::valueChanged, this, &Executor::gammaFilter);
    view->setControl(widget);
    controlWidget = widget;
}

void Executor::edgeRobertFilter(int threshold)
{
    QImage* image = view->getImageB();
    Filter* filter = new EdgeRobertFilter(threshold);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
    lastFilter = &Executor::edgeRobertFilter1;
}

void Executor::edgeRobertFilter1()
{
    EdgeWidget* widget = dynamic_cast<EdgeWidget*>(controlWidget);
    int threshold = widget->getValue();
    QImage* image = view->getImageB();
    Filter* filter = new EdgeRobertFilter(threshold);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
    lastFilter = &Executor::edgeRobertFilter1;
}

void Executor::edgeSobelButton()
{
    EdgeWidget* widget = new EdgeWidget();
    connect(widget->sliderA, &QSlider::valueChanged, this, &Executor::edgeSobelFilter);
    view->setControl(widget);
    controlWidget = widget;
}

void Executor::edgeSobelFilter(int threshold)
{
    QImage* image = view->getImageB();
    Filter* filter = new EdgeSobelFilter(threshold);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
    lastFilter = &Executor::edgeSobelFilter1;
}

void Executor::edgeSobelFilter1()
{
    EdgeWidget* widget = dynamic_cast<EdgeWidget*>(controlWidget);
    int threshold = widget->getValue();
    QImage* image = view->getImageB();
    Filter* filter = new EdgeSobelFilter(threshold);
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
    lastFilter = &Executor::edgeSobelFilter1;
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
    lastFilter = &Executor::embossFilter;
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
    lastFilter = &Executor::waterFilter;
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
    lastFilter = &Executor::blurFilter;
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
    lastFilter = &Executor::sharpenFilter;

}

void Executor::runLastFilter()
{
    if (lastFilter != nullptr){
        (((Executor*)this)->*lastFilter)();
    }
}

void Executor::setZoneA(ZoneA *value)
{
    zoneA = value;
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
    connect(view->ditheringErrorAct, SIGNAL(triggered()), this, SLOT(ditheringFloydButton()));
    connect(view->upscaleAct       , SIGNAL(triggered()), this, SLOT(upscaleFilter       ()));
    connect(view->rotateAct        , SIGNAL(triggered()), this, SLOT(rotateButton        ()));
    connect(view->gammaAct         , SIGNAL(triggered()), this, SLOT(gammaButton         ()));
    connect(view->edgeRobertAct    , SIGNAL(triggered()), this, SLOT(edgeRobertButton    ()));
    connect(view->edgeSobelAct     , SIGNAL(triggered()), this, SLOT(edgeSobelButton     ()));
    connect(view->embossAct        , SIGNAL(triggered()), this, SLOT(embossFilter        ()));
    connect(view->waterAct         , SIGNAL(triggered()), this, SLOT(waterFilter         ()));
    connect(view->blurAct          , SIGNAL(triggered()), this, SLOT(blurFilter          ()));
    connect(view->sharpenAct       , SIGNAL(triggered()), this, SLOT(sharpenFilter       ()));
    connect(zoneA, SIGNAL(lastFilter()), this, SLOT(runLastFilter()));
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
