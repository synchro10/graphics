#include "executor.h"

Executor::Executor(QObject *parent) : QObject(parent)
{
    view = QSharedPointer<View>(new View());
    model = QSharedPointer<Model>(new Model());
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

void Executor::setCImage(QImage *image)
{
    view->setImageC(image);
}

void Executor::setup()
{
    connect(view->blackWhiteAct, SIGNAL(triggered()), this, SLOT(blackWhiteFilter()));
    connect(view->negativeAct, SIGNAL(triggered()), this, SLOT(negativeFilter()));
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
