#include "graphics2d.h"

Graphics2D::Graphics2D()
{

}

void Graphics2D::drawLine(QPoint& point1, QPoint& point2, QRgb color, QImage& image)
{
    if (clippingLine(point1, point2, image)){
        int dx = std::abs(point1.x() - point2.x());
        int dy = std::abs(point1.y() - point2.y());
        if (dx > dy){
            drawLineX(point1, point2, color, image);
        } else {
            drawLineY(point1, point2, color, image);
        }
    }
}

bool Graphics2D::clippingLine(QPoint& p1, QPoint& p2, QImage& image)
{
    int height = image.height();
    int width = image.width();

    return true;
}

void Graphics2D::drawLineX(QPoint& point1, QPoint& point2, QRgb color, QImage& image)
{
    if (point1.x() > point2.x()){
        std::swap(point1, point2);
    }

    QRgb* pixels = reinterpret_cast<QRgb*>(image.bits());
    int width = image.bytesPerLine() / sizeof(QRgb);

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

    for(int i = 0; i <= dx; i++){
        pixels[x + y*width] = color;
        x++;
        error += dy;
        if (2*error > dx){
            error -= dx;
            y += sign;
        }
    }
}

void Graphics2D::drawLineY(QPoint& point1, QPoint& point2, QRgb color, QImage& image)
{
    if (point1.y() > point2.y()){
        std::swap(point1, point2);
    }

    QRgb* pixels = reinterpret_cast<QRgb*>(image.bits());
    int width = image.bytesPerLine() / sizeof(QRgb);

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

    for(int i = 0; i <= dy; i++){
        pixels[x + y*width] = color;
        y++;
        error += dx;
        if (2*error > dy){
            error -= dy;
            x += sign;
        }
    }
}
