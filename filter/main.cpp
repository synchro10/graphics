#include "view.h"
#include <QApplication>
#include "executor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Executor executor;
    executor.execute();

    return a.exec();
}
