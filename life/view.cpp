#include "view.h"
#include <QPushButton>
#include <QHBoxLayout>

View::View(QWidget *parent)
    : QMainWindow(parent), scroll(new QScrollArea)
{    
    field = std::unique_ptr<Field>(new Field(this));

    scroll->setWidget(field.get());
    setCentralWidget(scroll);

    resize(800, 600);
}

View::~View()
{
}

Field *View::getField() const
{
    return field.get();
}

