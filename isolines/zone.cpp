#include "zone.h"
#include <iostream>
#include <omp.h>

Zone::Zone(QWidget *parent) : QWidget(parent)
{
    image = QSharedPointer<QImage>(new QImage(width, height, QImage::Format_RGB32));
    values = QVector<double>();
    colors = QVector<QRgb>();
    defaultParams();
}

void Zone::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
//    QImage buffer = QImage(*image.data());
    fillImage();
    painter.drawImage(dirtyRect, *image.data(), dirtyRect);
}

void Zone::defaultParams()
{
    setFunction([](double x,double y){return x*x + y*y;});
    k = 10;
    m = 10;
    a = 0.0;
    b = 0.0;
    c = 5.0;
    d = 5.0;
    n = 9;
    colors.clear();
    for (int i = 0; i <= n; i++){
        colors.push_back(qRgb(255*i/n,255*(n-i)/n,0));
    }
    updateValues();
}

void Zone::setFunction(double (*func_)(double, double))
{
    function = func_;
}

void Zone::setColors(const QVector<QRgb> &value)
{
    colors = value;
}

void Zone::setK(int value)
{
    k = value;
}

void Zone::setM(int value)
{
    m = value;
}

void Zone::setN(int value)
{
    n = value;
}

void Zone::fillImage()
{
    if (function == nullptr){
        return;
    }
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
#pragma omp for
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            x = (double)(c-a)*i/width + a;
            y = (double)(d-b)*(height - j)/height + b;
            z = function(x, y);

            int number = floor(((z - minValue)/(maxValue - minValue))*(n+1));
            number = number < 0 ? 0 : number > n ? n : number;
            pixels[i + j*pixPerLine] = colors[number];
        }
    }
}

void Zone::updateValues()
{
    if (function == nullptr || n < 2){
        return;
    }
    double zMin = function(a,b);
    double zMax = function(a,b);
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            x = (double)(c-a)*i/width + a;
            y = (double)(d-b)*(height - j)/height + b;
            z = function(x, y);
            if (z < zMin){
                zMin = z;
            } else if (z > zMax){
                zMax = z;
            }
        }
    }
    double step = (zMax - zMin)/(n+1);
    values.clear();
    z = zMin;
    for(int i = 0; i < n; i++){
        z+=step;
        values.push_back(z);
    }
    this->minValue = zMin;
    this->maxValue = zMax;
    this->step = step;
}

