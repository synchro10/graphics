#include "zone.h"
#include <iostream>

Zone::Zone(QWidget *parent) : QWidget(parent)
{
    setFixedSize(size, size);
    image = QSharedPointer<QImage>(new QImage(size, size, QImage::Format_RGB32));
    image->fill(fontColor);
}

void Zone::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();

    painter.drawImage(dirtyRect, *image.data(), dirtyRect);
    painter.setPen(lineColor);
    drawDottedRect(100, 100, 200, 200);
    drawDottedRect(0, 0, size - 1, size - 1);
}

int Zone::getSize() const
{
    return size;
}

void Zone::drawDottedRect(int x0, int y0, int x1, int y1)
{
    QPoint p1 = QPoint(x0, y0);
    QPoint p2 = QPoint(x1, y0);
    QPoint p3 = QPoint(x1, y1);
    QPoint p4 = QPoint(x0, y1);
    drawDottedLine(p1, p2);
    drawDottedLine(p2,p3);
    drawDottedLine(p3,p4);
    drawDottedLine(p4,p1);
}

void Zone::drawDottedLine(QPoint &start, QPoint &end)
{
    if (start.x() == end.x()){
        if (start.y() < end.y()){
            drawDottedLineX(start, end);
        } else {
            drawDottedLineX(end, start);
        }
    } else if (start.y() == end.y()){
        if (start.x() < end.x()){
            drawDottedLineY(start, end);
        } else {
            drawDottedLineY(end, start);
        }
    }
}

void Zone::drawDottedLineY(QPoint &point1, QPoint &point2)
{
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int width = image->bytesPerLine() / sizeof(QRgb);

    int d = point2.x();
    int i = point1.x();
    int y = point1.y();

    for(; i <= d; i++){
        if (i % 8 < 4){
            pixels[i + y*width] = lineColor;
        } else {
            pixels[i + y*width] = fontColor;
        }
    }
}

void Zone::drawDottedLineX(QPoint &point1, QPoint &point2)
{
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int width = image->bytesPerLine() / sizeof(QRgb);

    int d = point2.y();
    int i = point1.y();
    int x = point1.x();

    for(; i <= d; i++){
        if (i % 8 < 4){
            pixels[x + i*width] = lineColor;
        } else {
            pixels[x + i*width] = fontColor;
        }
    }
}
