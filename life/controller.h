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

    void startGame(uint width, uint height, int cellSize);

signals:

public slots:
    void nextIteration();
    void run();
    void stop();
    void step();
    void clearField();
    void replaceMode();
    void xorMode();


private:
    void changeState(QPoint point);

    std::unique_ptr<Model> model;
    std::unique_ptr<View> view;
    Field* field = nullptr;

    QTimer* timer;
    const static int defaultDelay = 1000;

    bool isRun = false;
    bool isXOR = false;
};

#endif // CONTROLLER_H
