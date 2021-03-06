#include "drawingarea.h"
#include "zonea.h"

DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
    zoneA = new ZoneA(this);
    zoneB = new ZoneB(this);
    zoneC = new ZoneB(this);
    zoneA->setZoneB(zoneB);
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
}

void DrawingArea::open(const QString& fileName)
{
    QImage* image = new QImage(fileName);
    zoneA->setImage(image);
    zoneA->update();
}

void DrawingArea::save(const QString &fileName)
{
    QSharedPointer<QImage> image = QSharedPointer<QImage>(zoneC->getImage());
    image->save(fileName, "png");
}

void DrawingArea::select()
{
    zoneA->setSelect();
    zoneA->update();
}

void DrawingArea::moveToB()
{
    QImage* image_ = zoneA->getSelectedImage();
    if (image_ != nullptr){
        zoneB->setImage(image_);
    }
}

void DrawingArea::setCImage(QImage *image_)
{
    if (image_ != nullptr){
        zoneC->setImage(image_);
        zoneC->update();
    }
}

void DrawingArea::moveFromC()
{
    QImage* image_ = zoneC->getImage();
    zoneB->setImage(image_);
    zoneB->update();
}

QImage* DrawingArea::getImageB()
{
    return zoneB->getImage();
}

void DrawingArea::setControlPanel(QWidget *value)
{
    controlPanel = value;
    controlPanel->setParent(this);
    QLayoutItem * item;
    QWidget * widget;
    item = mainLayout->takeAt(1);
    widget = item->widget();
    widget->hide();
    delete widget;
    mainLayout->addWidget(controlPanel);
}

ZoneA *DrawingArea::getZoneA() const
{
    return zoneA;
}
