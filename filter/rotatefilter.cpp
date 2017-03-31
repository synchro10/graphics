#include "rotatefilter.h"
#include <QtMath>

RotateFilter::RotateFilter(int angle)
{
    this->angle = angle;
}

void RotateFilter::processImage()
{
    QImage* image1 = new QImage(*image.data());
    image1->fill(qRgb(255,255,255));
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    QRgb* pixels1 = reinterpret_cast<QRgb*>(image1->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);

    const int startX = -1*width/2;
    const int startY = -1*height/2;
    const int dx = width/2;
    const int dy = height/2;
    float cosA = qCos(qDegreesToRadians((float)angle));
    float sinA = qSin(qDegreesToRadians((float)angle));
    for(int j1 = startY; j1 < dy; j1++){
        for(int i1 = startX; i1 < dx; i1++){
            int i = i1*cosA + -1*j1*sinA;
            int j = i1*sinA + j1*cosA;
            i += dx;
            j += dy;
            if (belong(i, j)){
                pixels1[i1 - startX + (j1 - startY)*pixPerLine] = pixels[i + (j)*pixPerLine];
            }
        }
    }

    image = QSharedPointer<QImage>(image1);
}

bool RotateFilter::belong(int i, int j){
    return (0 <= i && i < width && 0 <= j && j < height);
}
