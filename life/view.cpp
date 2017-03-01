#include "view.h"

View::View(QWidget *parent)
    : QMainWindow(parent), scroll(new QScrollArea)
{    
    field = std::unique_ptr<Field>(new Field(this));

//    scroll->setBackgroundRole(QPalette::Dark);
    scroll->setWidget(field.get());
//    scroll->setVisible(false);

    setCentralWidget(scroll);

//    setCentralWidget(field.get());
    resize(800, 600);
}

View::~View()
{

}

Field *View::getField() const
{
    return field.get();
}

