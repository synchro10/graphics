#include "edgesobelfilter.h"

EdgeSobelFilter::EdgeSobelFilter(int value)
{
    this->threshold = value;
}

void EdgeSobelFilter::processImage()
{
    QImage* image1 = new QImage(*image.data());
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    QRgb* pixels1 = reinterpret_cast<QRgb*>(image1->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    for(int j = 2; j < height - 2; j++){
        for(int i = 2; i < width - 2; i++){
            QColor color = QColor(pixels[i - 1 + pixPerLine*(j-1)]);
            int Ya = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();

            color = QColor(pixels[i - 1 + pixPerLine*(j)]);
            int Yd = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();

            color = QColor(pixels[i - 1 + pixPerLine*(j+1)]);
            int Yg = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();

            color = QColor(pixels[i  + pixPerLine*(j-1)]);
            int Yb = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();

            color = QColor(pixels[i + pixPerLine*(j+1)]);
            int Yh = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();

            color = QColor(pixels[i + 1 + pixPerLine*(j-1)]);
            int Yc = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();

            color = QColor(pixels[i + 1 + pixPerLine*(j)]);
            int Yf = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();

            color = QColor(pixels[i + 1 + pixPerLine*(j+1)]);
            int Yi = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();

            int C = abs(Yc + 2*Yf + Yi - Ya - 2*Yd - Yg) + abs(Yg + 2*Yh + Yi - Ya - 2*Yb - Yc);
            if (C <= threshold){
                pixels1[i + pixPerLine*j] = qRgb(0, 0, 0);
            } else {
                pixels1[i + pixPerLine*j] = qRgb(255, 255, 255);
            }
        }
    }
    image = QSharedPointer<QImage>(image1);
}
