#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <QObject>
#include <QSharedPointer>
#include "view.h"
#include "model.h"

class Executor : public QObject
{
    Q_OBJECT
public:
    explicit Executor(QObject *parent = 0);
    void execute();
signals:

public slots:
private:
    QSharedPointer<View> view;
    QSharedPointer<Model> model;
};

#endif // EXECUTOR_H
