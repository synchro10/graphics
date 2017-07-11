#include "edgerobertfilter.h"

EdgeRobertFilter::EdgeRobertFilter(int value)
{
    this->threshold = value;
}

void EdgeRobertFilter::processImage()
{
    QImage* image1 = new QImage(*image.data());
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    QRgb* pixels1 = reinterpret_cast<QRgb*>(image1->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    for(int j = 1; j < height - 1; j++){
        for(int i = 1; i < width - 1; i++){
            QColor color = QColor(pixels[i + pixPerLine*j]);
            int Y00 = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();

            color = QColor(pixels[i + 1 + pixPerLine*(j+1)]);
            int Y11 = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();

            color = QColor(pixels[i + 1 + pixPerLine*j]);
            int Y10 = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();

            color = QColor(pixels[i + pixPerLine*(j+1)]);
            int Y01 = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();

            int F = abs(Y11 - Y00) + abs(Y10 - Y01);
            if (F <= threshold){
                pixels1[i + pixPerLine*j] = qRgb(0, 0, 0);
            } else {
                pixels1[i + pixPerLine*j] = qRgb(255, 255, 255);
            }
        }
    }
    image = QSharedPointer<QImage>(image1);
}
