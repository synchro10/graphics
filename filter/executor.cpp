#include "executor.h"

Executor::Executor(QObject *parent) : QObject(parent)
{
    view = QSharedPointer<View>(new View());
    threadPool = new QThreadPool(this);
    threadPool->setMaxThreadCount(1);
    setup();
}

void Executor::blackWhiteFilter()
{
    QImage* image = view->getImageB();
    Filter* filter = new BlackWhiteFilter();
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
}

void Executor::negativeFilter()
{
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
    std::cout << "В разработке" << std::endl;

}

void Executor::rotateFilter()
{
    std::cout << "В разработке" << std::endl;

}

void Executor::gammaFilter()
{
    std::cout << "В разработке" << std::endl;
}

void Executor::edgeRobertFilter()
{
    std::cout << "В разработке" << std::endl;

}

void Executor::edgeSobelFilter()
{
    std::cout << "В разработке" << std::endl;

}

void Executor::edgeSpecFilter()
{
    std::cout << "В разработке" << std::endl;

}

void Executor::embossFilter()
{
    std::cout << "В разработке" << std::endl;

}

void Executor::waterFilter()
{
    QImage* image = view->getImageB();
    Filter* filter = new WaterFilter();
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
}

void Executor::blurFilter()
{
    QImage* image = view->getImageB();
    Filter* filter = new BlurFilter();
    filter->setImage(image);
    connect(filter, &Filter::finished, this, &Executor::setCImage);
    addTask(filter);
}

void Executor::sharpenFilter()
{
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
    connect(view->rotateAct        , SIGNAL(triggered()), this, SLOT(rotateFilter        ()));
    connect(view->gammaAct         , SIGNAL(triggered()), this, SLOT(gammaFilter         ()));
    connect(view->edgeRobertAct    , SIGNAL(triggered()), this, SLOT(edgeRobertFilter    ()));
    connect(view->edgeSobelAct     , SIGNAL(triggered()), this, SLOT(edgeSobelFilter     ()));
    connect(view->edgeSpecAct      , SIGNAL(triggered()), this, SLOT(edgeSpecFilter      ()));
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
