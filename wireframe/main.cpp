#include "view.h"
#include "model.h"
#include "viewmodel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model model;
    View view;
    ViewModel vm;
    vm.init(&view, &model);
    vm.createConnects();
    view.show();

    return a.exec();
}
