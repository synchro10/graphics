#include "negativefilter.h"

NegativeFilter::NegativeFilter()
{

}

void NegativeFilter::processImage()
{
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    std::cout << "negative filter " << std::endl;
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            QColor color = QColor(pixels[i + pixPerLine*j]);
            color.setRed(255 - color.red());
            color.setGreen(255 - color.green());
            color.setBlue(255 - color.blue());
            pixels[i + pixPerLine*j] = color.rgb();
        }
    }
}
