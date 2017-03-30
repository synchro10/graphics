#include "sharpenfilter.h"


SharpenFilter::SharpenFilter()
{

}

void SharpenFilter::processImage()
{
    QImage* image1 = new QImage(*image.data());
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    QRgb* pixels1 = reinterpret_cast<QRgb*>(image1->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            QColor color = QColor(pixels[i + pixPerLine*j]);
            int red =   5*color.red();
            int green = 5*color.green();
            int blue =  5*color.blue();
            int weight = 5;
            if (j > 0){
                QColor color1 = QColor(pixels[i + pixPerLine*(j-1)]);
                red -= color1.red();
                green -= color1.green();
                blue -= color1.blue();
                weight--;
            }
            if (j < height - 1){
                QColor color1 = QColor(pixels[i + pixPerLine*(j+1)]);
                red -= color1.red();
                green -= color1.green();
                blue -= color1.blue();
                weight--;
            }
            if (i > 0){
                QColor color1 = QColor(pixels[i - 1 + pixPerLine*(j)]);
                red -= color1.red();
                green -= color1.green();
                blue -= color1.blue();
                weight--;
            }
            if (i < width - 1){
                QColor color1 = QColor(pixels[i  + 1 + pixPerLine*(j)]);
                red -= color1.red();
                green -= color1.green();
                blue -= color1.blue();
                weight--;
            }
            red/=weight;
            green/=weight;
            blue/=weight;
            red = red < 0 ? 0 : red;
            green = green < 0 ? 0 : green;
            blue = blue < 0 ? 0 : blue;
            red = red > 255 ? 255 : red;
            green = green > 255 ? 255 : green;
            blue = blue > 255 ? 255 : blue;
            color.setRed(red);
            color.setGreen(green);
            color.setBlue(blue);
            pixels1[i + pixPerLine*j] = color.rgb();
        }
    }
    image = QSharedPointer<QImage>(image1);
}
