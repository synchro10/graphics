#include "view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
{
    field = new Field(this);
    setCentralWidget(field);
    resize(800, 600);
}

View::~View()
{

}

Field *View::getField() const
{
    return field;
}

void View::setField(Field *value)
{
    field = value;
}
