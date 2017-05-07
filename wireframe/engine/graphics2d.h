#ifndef GRAPHICS2D_H
#define GRAPHICS2D_H

#include <QImage>
#include <QPoint>
#include <iostream>

class Graphics2D
{
public:
    Graphics2D();
    static void drawLine(QPoint& point1, QPoint& point2, QRgb color, QImage& image);
private:
    static bool clippingLine(QPoint& point1, QPoint& point2, QImage& image);
    static void drawLineX(QPoint& point1, QPoint& point2, QRgb color, QImage& image);
    static void drawLineY(QPoint& point1, QPoint& point2, QRgb color, QImage& image);
};

#endif // GRAPHICS2D_H
