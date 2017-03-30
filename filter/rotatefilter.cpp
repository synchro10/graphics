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
    for(int j = startY; j < dy; j++){
        for(int i = startX; i < dx; i++){
            int i1 = i*cosA + j*sinA;
            int j1 = -1*i*sinA + j+cosA;
            i1 += dx;
            j1 += dy;
            if (belong(i1, j1)){
                pixels1[i1 + (j1)*pixPerLine] = pixels[i - startX + (j - startY)*pixPerLine];
            }
        }
    }

    image = QSharedPointer<QImage>(image1);
}

bool RotateFilter::belong(int i, int j){
    return (0 <= i && i < width && 0 <= j && j < height);
}
