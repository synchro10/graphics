#include "view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
{
    field = new Field(this);
    setCentralWidget(field);
    resize(500, 500);
}

View::~View()
{

}
