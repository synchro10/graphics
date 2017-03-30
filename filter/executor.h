#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <QObject>
#include <QSharedPointer>
#include <QThreadPool>
#include "view.h"
#include "model.h"
#include "blackwhitefilter.h"
#include "negativefilter.h"

class Executor : public QObject
{
    Q_OBJECT
public:
    explicit Executor(QObject *parent = 0);
    void execute();

signals:

public slots:
    void blackWhiteFilter();
    void negativeFilter();
private:
    QSharedPointer<View> view;
    QSharedPointer<Model> model;
    QThreadPool* threadPool;

    void setCImage(QImage* image);
    void setup();
    void addTask(Filter* filter);
};

#endif // EXECUTOR_H
