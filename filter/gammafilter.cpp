#include "gammafilter.h"
#include <qmath.h>
#include <iostream>

GammaFilter::GammaFilter(double value)
{
    this->gamma = value;
}

void GammaFilter::processImage()
{
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            QColor color = QColor(pixels[i + pixPerLine*j]);
            double red = 255*pow((double)color.red()/255, gamma);
            double green = 255*pow((double)color.green()/255, gamma);
            double blue = 255*pow((double)color.blue()/255, gamma);
            pixels[i + pixPerLine*j] = qRgb((int)red, (int)green, (int)blue);
        }
    }
}
