#include "drawingarea.h"
#include "zonea.h"

DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
    zoneA = new ZoneA(this);
    zoneB = new ZoneA(this);
    zoneC = new ZoneA(this);
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

void DrawingArea::open(const QString& fileName)
{
    QImage* image = new QImage(fileName);
    zoneA->setImage(image);
}

void DrawingArea::select()
{
    zoneA->setSelect();
}
