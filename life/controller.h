#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <memory>
#include <QTimer>
#include "model.h"
#include "view.h"
#include "field.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

    void startGame(uint width, uint height);

signals:

public slots:
    void nextIteration();
private:

    std::unique_ptr<Model> model;
    std::unique_ptr<View> view;
    Field* field = nullptr;

    QTimer* timer;
    const static int defaultDelay = 1000;
};

#endif // CONTROLLER_H
