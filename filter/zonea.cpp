#include "zonea.h"
#include <iostream>

ZoneA::ZoneA(QWidget *parent)
{
    image = QSharedPointer<QImage>(new QImage(size, size, QImage::Format_RGB32));
    imagePrototype = QSharedPointer<QImage>();
    image->fill(fontColor);
    selectorSize = size;
}

void ZoneA::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    QImage buffer = QImage(*image.data());

    painter.setPen(lineColor);
    drawDottedRect(&buffer, 0, 0, size - 1, size - 1);
    if (isSelect && selectorSize != 0){
        paintSelector(&buffer);
    }

    painter.drawImage(dirtyRect, buffer, dirtyRect);
}

void ZoneA::setImage(QImage *image_)
{
    imagePrototype = QSharedPointer<QImage>(image_);
    QImage tmp = QImage(imagePrototype->scaled(size, size, Qt::KeepAspectRatio));
    height = tmp.height();
    width = tmp.width();
    image = QSharedPointer<QImage>(correctImage(&tmp));
    updateSelector();
}

void ZoneA::mouseMoveEvent(QMouseEvent *e)
{
    if (isSelect){
        int i = e->x();
        int j = e->y();
        if (i < 0){
            i = 0;
        }
        if (j < 0){
            j = 0;
        }
        if (i + selectorSize > width){
            i = width - selectorSize > 0 ? width - selectorSize : 0;
        }
        if (j + selectorSize > height){
            j = height - selectorSize > 0 ? height - selectorSize : 0;
        }
        selectorPosX = i;
        selectorPosY = j;
        update();
    }
}

QImage *ZoneA::correctImage(QImage *image2)
{
    if (image2->height() == size && image2->width() == size){
        return new QImage(*image2);
    }
    QImage* image1 = new QImage(size, size, QImage::Format_RGB32);
    QRgb* pixels1 = reinterpret_cast<QRgb*>(image1->bits());
    int width1 = image1->bytesPerLine() / sizeof(QRgb);
    QRgb* pixels2 = reinterpret_cast<QRgb*>(image2->bits());
    int width2 = image2->bytesPerLine() / sizeof(QRgb);
    int j = 0;
    for(; j < image2->height(); j++){
        int i = 0;
        for(; i < image2->width(); i++){
            pixels1[i + width1*j] = pixels2[i + width2*j];
        }
        for(; i < size; i++){
            pixels1[i + width1*j] = fontColor;
        }
    }
    for(; j < size; j++){
        for(int i = 0; i < size; i++){
            pixels1[i + width1*j] = fontColor;
        }
    }
    return image1;
}

void ZoneA::updateSelector()
{
    selectorPosX = 0;
    selectorPosY = 0;
    int biggestSide = std::max<int>(imagePrototype->height(), imagePrototype->width());
    biggestSide = std::max<int>(biggestSide, size);
    if (biggestSide == size){
        selectorSize = size;
    } else {
        selectorSize = (size*size)/biggestSide;
    }
}

void ZoneA::paintSelector(QImage* image_)
{
    drawDottedRect(image_, selectorPosX, selectorPosY, selectorPosX + selectorSize - 1, selectorPosY + selectorSize - 1);
}
