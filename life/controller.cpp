#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{

}

void Controller::setModel(const Model &value)
{
    model = value;
}

void Controller::setView(const View &value)
{
    view = value;
}
