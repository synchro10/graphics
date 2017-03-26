#include "view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    area = new DrawingArea(this);
    setCentralWidget(area);
}

View::~View()
{

}
