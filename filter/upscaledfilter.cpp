#include "upscaledfilter.h"

UpscaledFilter::UpscaledFilter()
{

}

void UpscaledFilter::processImage()
{
    QImage* image1 = new QImage(*image.data());
    image1->fill(qRgb(255,255,255));
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    QRgb* pixels1 = reinterpret_cast<QRgb*>(image1->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);

    int startX = width/4;
    int startY = height/4;
    int dx = width/2;
    int dy = height/2;
    for(int j = 0; j < dy; j++){
        for(int i = 0; i < dx; i++){
            pixels1[2*i + 2*j*pixPerLine] = pixels[i + startX + (j+startY)*pixPerLine];
            pixels1[2*i + 1 + 2*j*pixPerLine] = pixels[i + startX + (j+startY)*pixPerLine];
            pixels1[2*i + (2*j+1)*pixPerLine] = pixels[i + startX + (j+startY)*pixPerLine];
            pixels1[2*i +1 + (2*j+1)*pixPerLine] = pixels[i + startX + (j+startY)*pixPerLine];
        }
    }

    image = QSharedPointer<QImage>(image1);
    //blur copypaste
    image1 = new QImage(*image.data());
    pixels = reinterpret_cast<QRgb*>(image->bits());
    pixels1 = reinterpret_cast<QRgb*>(image1->bits());
    pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            QColor color = QColor(pixels[i + pixPerLine*j]);
            int red =   2*color.red();
            int green = 2*color.green();
            int blue =  2*color.blue();
            int weight = 2;
            if (j > 0){
                QColor color1 = QColor(pixels[i + pixPerLine*(j-1)]);
                red += color1.red();
                green += color1.green();
                blue += color1.blue();
                weight++;
            }
            if (j < height - 1){
                QColor color1 = QColor(pixels[i + pixPerLine*(j+1)]);
                red += color1.red();
                green += color1.green();
                blue += color1.blue();
                weight++;
            }
            if (i > 0){
                QColor color1 = QColor(pixels[i - 1 + pixPerLine*(j)]);
                red += color1.red();
                green += color1.green();
                blue += color1.blue();
                weight++;
            }
            if (i < width - 1){
                QColor color1 = QColor(pixels[i  + 1 + pixPerLine*(j)]);
                red += color1.red();
                green += color1.green();
                blue += color1.blue();
                weight++;
            }
            color.setRed(red/=weight);
            color.setGreen(green/=weight);
            color.setBlue(blue/=weight);
            pixels1[i + pixPerLine*j] = color.rgb();
        }
    }
    image = QSharedPointer<QImage>(image1);
}
