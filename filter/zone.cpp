#include "zone.h"

Zone::Zone(QWidget *parent) : QWidget(parent)
{
    setFixedSize(size, size);
}

void Zone::drawDottedRect(QImage* image, int x0, int y0, int x1, int y1)
{
    QPoint p1 = QPoint(x0, y0);
    QPoint p2 = QPoint(x1, y0);
    QPoint p3 = QPoint(x1, y1);
    QPoint p4 = QPoint(x0, y1);
    drawDottedLine(image, p1, p2);
    drawDottedLine(image, p2, p3);
    drawDottedLine(image, p3, p4);
    drawDottedLine(image, p4, p1);
}

void Zone::drawDottedLine(QImage* image, QPoint &start, QPoint &end)
{
    if (start.x() == end.x()){
        if (start.y() < end.y()){
            drawDottedLineX(image, start, end);
        } else {
            drawDottedLineX(image, end, start);
        }
    } else if (start.y() == end.y()){
        if (start.x() < end.x()){
            drawDottedLineY(image, start, end);
        } else {
            drawDottedLineY(image, end, start);
        }
    }
}

void Zone::drawDottedLineY(QImage* image, QPoint &point1, QPoint &point2)
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

void Zone::drawDottedLineX(QImage* image, QPoint &point1, QPoint &point2)
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
