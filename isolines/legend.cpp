#include "legend.h"

Legend::Legend(QWidget *parent) : QWidget(parent)
{
    setFixedSize(width + 20, height + 20);
    image = QSharedPointer<QImage>(new QImage(width, height, QImage::Format_RGB32));
}

void Legend::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    dirtyRect.setTop(15);
    if (colors.isEmpty()){
        return;
    }
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    for(int i = 0; i < width; i++){
        int number = (i*(n+1))/width;
        QRgb color;
        if (!isInterpolate){
            color = (colors)[number];
        } else {
            color = getInterpolateColor(i);
        }
        for(int j = 0; j < height; j++){
            pixels[i + pixPerLine*j] = color;
        }
    }
    painter.drawImage(dirtyRect, *image.data(), dirtyRect);
    if (values.isEmpty() || n > 12){
        return;
    }
    for(int i = 1; i <= n; i++){
        QString str = QString::number((values)[i-1], 'f', 2);
        painter.drawText(i*width/(n+1) - str.length()*6/2, 10, str);
    }
}

void Legend::setN(int value)
{
    n = value;
}

void Legend::setInterpolation()
{
    isInterpolate = !isInterpolate;
}

void Legend::setColors(const QVector<QRgb> &value)
{
    colors = QVector<QRgb>(value);
}

QRgb Legend::getInterpolateColor(int i)
{
    int number = (i*(n+1))/width;
    QColor color1 = QColor((colors)[number]);
    if (number >= n){
        return color1.rgb();
    }
    QColor color2 = QColor((colors)[number+1]);
    int red1  = color1.red();
    int red2 = color2.red();
    int green1 = color1.green();
    int green2 = color2.green();
    int blue1 = color1.blue();
    int blue2 = color2.blue();
    int z = i;
    int z0 = (width*number)/(n+1);
    int z1 = (width*(number+1))/(n+1);
    int red = (((double)red1*(z1 - z)/(z1 - z0) + (double)red2*(z - z0)/ (z1 - z0)));
    int green = (((double)green1*(z1 - z)/ (z1 - z0) +
            (double)green2*(z - z0)/ (z1 - z0)));
    int blue = (((double)blue1*(z1 - z)/ (z1 - z0) +
            (double)blue2*(z - z0)/ (z1 - z0)));
    red = red > 255 ? 255 : red < 0 ? 0 : red;
    blue = blue > 255 ? 255 : blue < 0 ? 0 : blue;
    green = green > 255 ? 255 : green < 0 ? 0 : green;
    return qRgb(red, green, blue);
}

void Legend::setValues(const QVector<double> &value)
{
    values = QVector<double>(value);
}

void Legend::init(int n, const QVector<QRgb> &colors, const QVector<double> &values)
{
    this->n = n;
    this->colors = QVector<QRgb>(colors);
    this->values = QVector<double>(values);
}
