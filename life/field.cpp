#include "field.h"
#include <QRgb>
#include <QtWidgets>
#include <iostream>


Field::Field(QWidget *parent) : QWidget(parent)
{
    lineColor = qRgb(0,0,0);
    cellColor = qRgb(10,255,10);
    fontColor = qRgb(255,255,255);
    image = new QImage(DEFAULT_WIDTH, DEFAULT_HEIGHT, QImage::Format_RGB32);
    image->fill(fontColor);
}

Field::~Field(){
    if (image != nullptr){
        delete image;
    }
}

void Field::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    uchar* arr = image->bits();
    QRgb* pixels = reinterpret_cast<QRgb*>(arr);

    drawLine(QPoint(-10,-10), QPoint(400, 300));
    drawLine(QPoint(0,300), QPoint(400, 0));
    drawLine(QPoint(0,0), QPoint(300, 400));
    drawLine(QPoint(300,0), QPoint(0, 400));


    painter.drawImage(dirtyRect, *image, dirtyRect);
}

void Field::drawLine(QPoint point1, QPoint point2)
{
    clippingLine(&point1, &point2);
    int dx = std::abs(point1.x() - point2.x());
    int dy = std::abs(point1.y() - point2.y());
    if (dx > dy){
        drawLineX(point1, point2);
    } else {
        drawLineY(point1, point2);
    }
}

void Field::clippingLine(QPoint *point1, QPoint *point2)
{

}

void Field::drawLineX(QPoint point1, QPoint point2)
{
    if (point1.x() > point2.x()){
        std::swap(point1, point2);
    }

    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int width = image->bytesPerLine() / sizeof(QRgb);

    int dy = point2.y() - point1.y();
    int dx = point2.x() - point1.x();
    int sign = 1;
    if (dy < 0){
        dy *= -1;
        sign = -1;
    }
    int error = 0;
    int y = point1.y();
    int x = point1.x();

    for(int i = 0; i < dx; i++){
        pixels[x + y*width] = lineColor;
        x++;
        error += dy;
        if (2*error > dx){
            error -= dx;
            y += sign;
        }
    }
}

void Field::drawLineY(QPoint point1, QPoint point2)
{
    if (point1.y() > point2.y()){
        std::swap(point1, point2);
    }

    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int width = image->bytesPerLine() / sizeof(QRgb);

    int dx = point2.x() - point1.x();
    int dy = point2.y() - point1.y();
    int sign = 1;
    if (dx < 0){
        dx *= -1;
        sign = -1;
    }
    int error = 0;
    int x = point1.x();
    int y = point1.y();

    for(int i = 0; i < dy; i++){
        pixels[x + y*width] = lineColor;
        y++;
        error += dx;
        if (2*error > dy){
            error -= dy;
            x += sign;
        }
    }
}


