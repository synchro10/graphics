#include "blackwhitefilter.h"


BlackWhiteFilter::BlackWhiteFilter()
{

}

void BlackWhiteFilter::processImage()
{
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    int Y = 0;
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            QColor color = QColor(pixels[i + pixPerLine*j]);
            Y = 0.3*color.red() + 0.59*color.green()+0.11*color.blue();
            color.setRed(Y);
            color.setGreen(Y);
            color.setBlue(Y);
            pixels[i + pixPerLine*j] = color.rgb();
        }
    }
}
