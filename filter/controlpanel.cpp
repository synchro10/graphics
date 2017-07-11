#include "controlpanel.h"
#include <iostream>

ControlPanel::ControlPanel(QWidget *parent) : QWidget(parent)
{
    setup();
}

void ControlPanel::setup()
{
    setFixedSize(350*3, 200);
}
