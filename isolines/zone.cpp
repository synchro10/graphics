#include "zone.h"
#include <iostream>

Zone::Zone(QWidget *parent) : QWidget(parent)
{
    setFixedSize(width + 20, height + 20);
    image = QSharedPointer<QImage>(new QImage(width, height, QImage::Format_RGB32));
    values = QVector<double>();
    colors = QVector<QRgb>();
    defaultParams();
}

void Zone::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    fillImage();
    painter.drawImage(dirtyRect, *image.data(), dirtyRect);
}

void Zone::defaultParams()
{
    setFunction([](double x,double y){return x + y;});
//    setFunction([](double x,double y){return exp(-x*x - y*y/2)*cos(4*x)+exp(-3*((x+0.5)*(x+0.5)+y*y/2));});
    k = 10;
    m = 10;
    a = -2.0;
    c = -4.0;
    b = 2.0;
    d = 4.0;
    n = 10;
    colors.clear();
    for (int i = 0; i <= n; i++){
//        colors.push_back(qRgb(255*i/n,255*(n-i)/n,0));
        colors.push_back(qRgb(255*(n-i)/n,255*(n-i)/n,255*(n-i)/n));
//        if (i == n -1){
//            colors.push_back(qRgb(255,255,255));
//        } else {
//            colors.push_back(qRgb(255*(n-i)/n,255*(n-i)/n,255*(n-i)/n));
//        }
//        std::cout << 255*i/n << " " << 255*(n-i)/n << " " << 0 << std::endl;
    }
    updateValues();
    initLegend();
}

void Zone::setInterpolation()
{
    isInterpolate = !isInterpolate;
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

void Zone::setLegend(Legend *value)
{
    legend = value;
    initLegend();
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
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            x = (double)(b-a)*i/width + a;
            y = (double)(d-c)*(height - j)/height + c;
            z = function(x, y);

            int number = floor(((z - minValue)/(maxValue - minValue))*(n+1));
            number = number < 0 ? 0 : number > n ? n : number;
            if (!isInterpolate || number >= n){
                pixels[i + j*pixPerLine] = colors[number];
            } else {
                QColor color1 = QColor(colors[number]);
                QColor color2 = QColor(colors[number+1]);
                int red1  = color1.red();
                int red2 = color2.red();
                int green1 = color1.green();
                int green2 = color2.green();
                int blue1 = color1.blue();
                int blue2 = color2.blue();
                int red = (((double)red1*(values[number+1] - z)/ (values[number+1] - values[number]) +
                        (double)red2*(z - values[number])/ (values[number+1] - values[number])));
                int green = (((double)green1*(values[number+1] - z)/ (values[number+1] - values[number]) +
                        (double)green2*(z - values[number])/ (values[number+1] - values[number])));
                int blue = (((double)blue1*(values[number+1] - z)/ (values[number+1] - values[number]) +
                        (double)blue2*(z - values[number])/ (values[number+1] - values[number])));
                red = red > 255 ? 255 : red < 0 ? 0 : red;
                blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
                green = green > 255 ? 255 : green < 0 ? 0 : green;

                pixels[i + j*pixPerLine] = qRgb(red, green, blue);
            }

        }
    }
}

void Zone::drawIsoline()
{

}

void Zone::updateValues()
{
    if (function == nullptr || n < 2){
        return;
    }
    double zMin = function(a,c);
    double zMax = function(a,c);
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            x = (double)(b-a)*i/width + a;
            y = (double)(d-c)*(height - j)/height + c;
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
    values.push_back(zMax);
    this->minValue = zMin;
    this->maxValue = zMax;
    this->step = step;

}

void Zone::initLegend()
{
    if (legend == nullptr){
        return;
    }
    legend->setN(n);
    legend->setColors(&colors);
}

