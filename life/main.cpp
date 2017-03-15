#include "view.h"
#include "controller.h"
#include <QApplication>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Controller controller;
    controller.startGame(180,100,7);

    return a.exec();
}
