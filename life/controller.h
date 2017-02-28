#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "model.h"
#include "view.h"
#include "field.h"

class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(QObject *parent = 0);
    ~Controller();

    void startGame();

    void setModel(const Model &value);

    void setView(const View &value);

signals:

public slots:

private:
    void nextIteration();

    Model model;
    View view;
};

#endif // CONTROLLER_H
