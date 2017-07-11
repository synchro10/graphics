#include "dithringfloydfilter.h"

DithringFloydFilter::DithringFloydFilter(int red, int green, int blue)
{
    this->red = red;
    this->green = green;
    this->blue = blue;
}

void DithringFloydFilter::processImage()
{
    QImage* image1 = new QImage(*image.data());
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    QRgb* pixels1 = reinterpret_cast<QRgb*>(image1->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            QColor color = pixels[i + pixPerLine*j];
            const int red =   getNearColor(color.red(), this->red);
            const int green = getNearColor(color.green(), this->green);
            const int blue =  getNearColor(color.blue(), this->blue);
            pixels1[i + pixPerLine*j] = qRgb(red, green, blue);

            const int errorRed = color.red() - red;
            const int errorBlue = color.blue() - blue;
            const int errorGreen = color.green() - green;
            if (i < width - 1){
                color = pixels[i + 1 + pixPerLine*j];
                int red1 = color.red() + 5*errorRed/16;
                int green1 = color.green() + 5*errorGreen/16;
                int blue1 = color.blue() + 5*errorBlue/16;
                red1 = red1 < 0 ? 0 : red1 > 255 ? 255 : red1;
                green1 = green1 < 0 ? 0 : green1 > 255 ? 255 : green1;
                blue1 = blue1 < 0 ? 0 : blue1 > 255 ? 255 : blue1;
                pixels[i + 1 + pixPerLine*j] = qRgb(red1, green1, blue1);
            }
            if (j < height - 1){
                color = pixels[i + pixPerLine*(j+1)];
                int red1 = color.red() + 7*errorRed/16;
                int green1 = color.green() + 7*errorGreen/16;
                int blue1 = color.blue() + 7*errorBlue/16;
                red1 = red1 < 0 ? 0 : red1 > 255 ? 255 : red1;
                green1 = green1 < 0 ? 0 : green1 > 255 ? 255 : green1;
                blue1 = blue1 < 0 ? 0 : blue1 > 255 ? 255 : blue1;
                pixels[i + pixPerLine*(j+1)] = qRgb(red1, green1, blue1);
            }
            if (j < height - 1 && i > 0){
                color = pixels[i - 1 + pixPerLine*(j+1)];
                int red1 = color.red() + 3*errorRed/16;
                int green1 = color.green() + 3*errorGreen/16;
                int blue1 = color.blue() + 3*errorBlue/16;
                red1 = red1 < 0 ? 0 : red1 > 255 ? 255 : red1;
                green1 = green1 < 0 ? 0 : green1 > 255 ? 255 : green1;
                blue1 = blue1 < 0 ? 0 : blue1 > 255 ? 255 : blue1;
                pixels[i - 1 + pixPerLine*(j+1)] = qRgb(red1, green1, blue1);
            }
            if (j < height - 1 && i < width - 1){
                color = pixels[i + 1 + pixPerLine*(j+1)];
                int red1 = color.red() + errorRed/16;
                int green1 = color.green() + errorGreen/16;
                int blue1 = color.blue() + errorBlue/16;
                red1 = red1 < 0 ? 0 : red1 > 255 ? 255 : red1;
                green1 = green1 < 0 ? 0 : green1 > 255 ? 255 : green1;
                blue1 = blue1 < 0 ? 0 : blue1 > 255 ? 255 : blue1;
                pixels[i + 1 + pixPerLine*(j+1)] = qRgb(red1, green1, blue1);
            }
        }
    }
    image = QSharedPointer<QImage>(image1);
}

int DithringFloydFilter::getNearColor(int color, int division)
{
    int step = 1;

    if (2 == division) {
        step = 128;
    } else {
        step = 255 / (division - 1);
    }

    int nearColor = ((color + step / 2) / step) * step;
    nearColor = nearColor > 255 ? 255 : nearColor < 0 ? 0 : nearColor;
    return nearColor;
}
