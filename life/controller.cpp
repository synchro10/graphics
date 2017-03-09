#include "controller.h"
#include <QTimer>

Controller::Controller(QObject *parent) : QObject(parent)
{
    model = std::unique_ptr<Model>(new Model());
    view = std::unique_ptr<View>(new View());
    field = view->getField();
    field->setField(&model->getCurrentState());
    timer = new QTimer(this);
    timer->setInterval(defaultDelay);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextIteration()));
}


Controller::~Controller()
{

}

void Controller::startGame(uint width, uint height, int cellSize)
{
    model->resize(width, height);
    field->changeParam(width, height, cellSize);

    //todo

    //tmp demonstration
    model->aliveCell(10,12);
    model->aliveCell(11,12);
    model->aliveCell(12,10);
    model->aliveCell(12,11);
    model->aliveCell(12,12);

    view->show();
    timer->start();
}

void Controller::nextIteration()
{
    model->countNextState();
    field->setField(&model->getCurrentState());
    field->update();
}

void Controller::run()
{
    if (!isRun){
        timer->start();
        isRun = true;
    }
}

void Controller::stop()
{
    if (isRun){
        timer->stop();
        isRun = false;
    }
}

void Controller::step()
{

}

void Controller::clearField()
{

}

void Controller::replaceMode()
{

}

void Controller::xorMode()
{

}



void Controller::changeState(QPoint point)
{

}



