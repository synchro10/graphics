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

//    drawLine(QPoint(-10,-10), QPoint(400, 300));
//    drawLine(QPoint(0,300), QPoint(400, 0));
//    drawLine(QPoint(0,0), QPoint(300, 400));
//    drawLine(QPoint(300,0), QPoint(0, 400));

    drawGrid();
//    fillCell(0,0, cellColor);

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
    //unsafe
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

uint Field::getCellWidth() const
{
    return cellWidth;
}

void Field::setCellWidth(const uint &value)
{
    cellWidth = value;
}

void Field::drawHexagon(uint x, uint y)
{
    if (x > cellWidth || y > cellHeight){
        return;
    }

    int rsin30 = cellSize/2;
    int rcos30 = cellSize*sqrt(3)/2;

    int y0 = y * (2 * cellSize - rsin30);
    int x0 = 0;
    if (y & 0u == 0){
        x0 = 2 * x * rcos30 + rcos30;
    } else {
         x0 = 2 * x * rcos30;
    }

    QPoint point1 = QPoint(x0,              y0 + rsin30);
    QPoint point2 = QPoint(x0 + rcos30,     y0 );
    QPoint point3 = QPoint(x0 + 2*rcos30,   y0 + rsin30);
    QPoint point4 = QPoint(x0 + 2*rcos30,   y0 + 2*cellSize - rsin30);
    QPoint point5 = QPoint(x0 + rcos30,     y0 + 2*cellSize);
    QPoint point6 = QPoint(x0,              y0 + 2*cellSize - rsin30);

    drawLine(point1, point2);
    drawLine(point2, point3);
    drawLine(point1, point6);
    drawLine(point3, point4);
    drawLine(point6, point5);
    drawLine(point5, point4);
}

void Field::drawGrid()
{
    for(uint i = 0; i < cellHeight; i++){
        for(uint j = 0; j < cellWidth - i%2; j++){
            drawHexagon(j, i);
            fillCell(j,i, cellColor);
        }
    }
}

void Field::fillCell(uint x, uint y, QRgb color)
{
    if (x > cellWidth || y > cellHeight){
        return;
    }

    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int width = image->bytesPerLine() / sizeof(QRgb);

    int rsin30 = cellSize/2;
    int rcos30 = cellSize*sqrt(3)/2;

    int y0 = y * (2 * cellSize - rsin30);
    int y1 = y0 + 2 * cellSize;
    int x0 = 0;
    if (y & 0u == 0){
        x0 = 2 * x * rcos30 + 2*rcos30;
    } else {
         x0 = 2 * x * rcos30 + rcos30;
    }

    for(int i = y0; i < y1; i++){
        for(int j = x0; j < x0 + rcos30; j++){
            if (pixels[i * width + j] == lineColor){
                break;
            }
            pixels[i * width + j] = color;
        }
        for(int j = x0; j > x0 - rcos30; j--){
            if (pixels[i * width + j] == lineColor){
                break;
            }
            pixels[i * width + j] = color;
        }
    }
}

uint Field::getCellHeight() const
{
    return cellHeight;
}

void Field::setCellHeight(const uint &value)
{
    cellHeight = value;
}

uint Field::getCellSize() const
{
    return cellSize;
}

void Field::setCellSize(const uint &value)
{
    cellSize = value;
}


