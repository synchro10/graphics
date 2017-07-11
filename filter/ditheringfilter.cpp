#include "ditheringfilter.h"

DitheringFilter::DitheringFilter()
{

}

void DitheringFilter::processImage()
{
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            QColor color = QColor(pixels[i + pixPerLine*j]);
            int red =   color.red();
            int green = color.green();
            int blue =  color.blue();
            red = red > matrix[i%matrixSize + matrixSize*(j%matrixSize)] ? 255 : 0;
            green = green > matrix[i%matrixSize + matrixSize*(j%matrixSize)] ? 255 : 0;
            blue = blue > matrix[i%matrixSize + matrixSize*(j%matrixSize)] ? 255 : 0;
            pixels[i + pixPerLine*j] = qRgb(red, green, blue);
        }
    }
}
