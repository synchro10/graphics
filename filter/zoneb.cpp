#include "zoneb.h"
#include <iostream>

ZoneB::ZoneB(QWidget *parent)
{
    image = QSharedPointer<QImage>(new QImage(size, size, QImage::Format_RGB32));
    image->fill(fontColor);
}

void ZoneB::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    QImage buffer = QImage(*image.data());

    painter.setPen(lineColor);
    drawDottedRect(&buffer, 0, 0, size - 1, size - 1);

    painter.drawImage(dirtyRect, buffer, dirtyRect);
}

void ZoneB::setImage(QImage *image_)
{
    if(image_->width() != size || image_->height() != size){
        std::cout << "don't set image cause of bad size" << image_->width() << " " << image_->height() << std::endl;
        delete image_;
        return;
    }
    image = QSharedPointer<QImage>(image_);
}

//return copy of image
QImage *ZoneB::getImage()
{
   return new QImage(*image.data());
}
