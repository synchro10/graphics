#include "view.h"
#include "controller.h"
#include <QApplication>
#include <memory>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    std::shared_ptr<View> view = std::shared_ptr<View>(new View());
//    view.get()->show();
    Controller controller;
//    controller.setView(view);
    controller.startGame(33,33);

    return a.exec();
}
