#include "executor.h"

Executor::Executor(QObject *parent) : QObject(parent)
{
    view = QSharedPointer<View>(new View());
    model = QSharedPointer<Model>(new Model());
}

void Executor::execute()
{
    view->show();
}
