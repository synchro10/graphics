#include "embossfilter.h"

EmbossFilter::EmbossFilter()
{

}

void EmbossFilter::processImage()
{
    QImage* image1 = new QImage(*image.data());
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    QRgb* pixels1 = reinterpret_cast<QRgb*>(image1->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            int red =   0;
            int green = 0;
            int blue =  0;
            if (j > 0){
                QColor color1 = QColor(pixels[i + pixPerLine*(j-1)]);
                red += color1.red();
                green += color1.green();
                blue += color1.blue();
            }
            if (j < height - 1){
                QColor color1 = QColor(pixels[i + pixPerLine*(j+1)]);
                red -= color1.red();
                green -= color1.green();
                blue -= color1.blue();
            }
            if (i > 0){
                QColor color1 = QColor(pixels[i - 1 + pixPerLine*(j)]);
                red -= color1.red();
                green -= color1.green();
                blue -= color1.blue();
            }
            if (i < width - 1){
                QColor color1 = QColor(pixels[i  + 1 + pixPerLine*(j)]);
                red += color1.red();
                green += color1.green();
                blue += color1.blue();
            }
            red += 128;
            green += 128;
            blue += 128;
            red = red <= 255 ? red : 255;
            green = green <= 255 ? green : 255;
            blue = blue <= 255 ? blue : 255;
            pixels1[i + pixPerLine*j] = qRgb(red, green, blue);
        }
    }
    image = QSharedPointer<QImage>(image1);
}
