#include "drawingarea.h"

DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
    zoneA = new Zone(this);
    zoneB = new Zone(this);
    zoneC = new Zone(this);
    controlPanel = new ControlPanel(this);
    zoneLayout = new QHBoxLayout;
    zoneLayout->setSpacing(20);
    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    zoneLayout->addWidget(zoneA);
    zoneLayout->addWidget(zoneB);
    zoneLayout->addWidget(zoneC);
    mainLayout->addLayout(zoneLayout);
    mainLayout->addWidget(controlPanel);
    setLayout(mainLayout);
}

void DrawingArea::paintEvent(QPaintEvent *event)
{
    zoneA->update();
    zoneB->update();
    zoneC->update();
}
