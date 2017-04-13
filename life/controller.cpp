#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    model = std::unique_ptr<Model>(new Model());
    view = std::unique_ptr<View>(new View());
    field = view->getField();
    view->setModel(model.get());
    field->setModel(model.get());
    field->init();
}

void Controller::startGame(uint width, uint height, int cellSize)
{
    model->resize(width, height);
    field->changeParam(width, height, cellSize);
    view->show();
}





