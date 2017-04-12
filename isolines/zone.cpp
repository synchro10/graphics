#include "zone.h"
#include <iostream>

Zone::Zone(QWidget *parent) : QWidget(parent)
{
    setFixedSize(width + 20, height + 20);
    image = QSharedPointer<QImage>(new QImage(width, height, QImage::Format_RGB32));
    values = QVector<double>();
    customIsolines = QVector<double>();
    colors = QVector<QRgb>();
    defaultParams();
}

void Zone::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    fillImage();
    drawGrid();
    drawAllIsolines();
    painter.drawImage(dirtyRect, *image.data(), dirtyRect);
}

void Zone::defaultParams()
{
//    setFunction([](double x,double y){return x + y;});
    setFunction([](double x,double y){return exp(-x*x - y*y/2)*cos(4*x)+exp(-3*((x+0.5)*(x+0.5)+y*y/2));});
//    setFunction([](double x,double y){return x;});
    k = 50;
    m = 50;
    a = -2.0;
    c = -4.0;
    b = 2.0;
    d = 4.0;
    n = 10;
    colors.clear();
    for (int i = 0; i <= n; i++){
//        colors.push_back(qRgb(255*(n-i)/n,255*(n-i)/n,255*(n-i)/n));
        colors.push_back(qRgb(0,255*(n-i)/n,0));
    }
    updateValues();
    initLegend();
}

void Zone::setInterpolation()
{
    isInterpolate = !isInterpolate;
    reset();
}

void Zone::setGrid()
{
    isGrid = !isGrid;
    reset();
}

void Zone::setIsoline()
{
    isIsoline = !isIsoline;
    reset();
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

const Options Zone::getOptions()
{
    return Options(k, m, a, b, c, d);
}

void Zone::setOptions(const Options options)
{
    if (options.a < options.b && options.c < options.d){
        this->k = options.k;
        this->m = options.m;
        this->a = options.a;
        this->b = options.b;
        this->c = options.c;
        this->d = options.d;
        reset();
    } else {
        QMessageBox::about(this, tr("Error"),
                           tr("incorrect options"));
    }
}

void Zone::addIsoline(double value)
{
    customIsolines.push_back(value);
}

void Zone::clearIsolines()
{
    customIsolines.clear();
    reset();
}

void Zone::mousePressEvent(QMouseEvent *e)
{
    if (!isIsoline || function == nullptr){
        return;
    }
    auto coord = coordFromPixel(e->x(), e->y());
    double value = function(coord.first, coord.second);
    addIsoline(value);
    isLastIsolineDrawn = false;
    update();
}

void Zone::mouseMoveEvent(QMouseEvent *e)
{
    if (0 <= e->x() && e->x() < width && 0 <= e->y() && e->y() < height){
        if (!customIsolines.isEmpty()){
            customIsolines.removeLast();
            reset();
        }
        mousePressEvent(e);
    }
}

void Zone::fillImage()
{
    if (function == nullptr || isMapDrawn){
        return;
    }
    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
    for(int j = 0; j < height; j++){
        for(int i = 0; i < width; i++){
            auto coord = coordFromPixel(i,j);
            x = coord.first;
            y = coord.second;
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
    isMapDrawn = true;
}

void Zone::drawGrid()
{
    if (!isGrid || isGridDrawn){
        return;
    }
    QPoint point1;
    QPoint point2;
    for(int i = 0; i <= k; i++){
        point1 = QPoint(i*(width-1)/k, 0);
        point2 = QPoint(i*(width-1)/k, height-1);
        drawLine(point1, point2);
    }
    for(int i = 0; i <= m; i++){
        point1 = QPoint(0, i*(height-1)/m);
        point2 = QPoint(width-1, i*(height-1)/m);
        drawLine(point1, point2);
    }
    isGridDrawn = true;
}

void Zone::drawAllIsolines()
{
    if (!isIsoline){
        return;
    } else if (!isIsolineDrawn){
        for(int j = 0; j < m; j++){
            for(int i = 0; i < k; i++){
                const ParametrsIsoline& params = ParametrsIsoline(this, i,j);
                for(auto value: values){
                    drawIsoline(params, value);
                }
                for(auto value: customIsolines){
                    drawIsoline(params, value);
                }
            }
        }
        isIsolineDrawn = true;
        isLastIsolineDrawn = true;
    } else if (!isLastIsolineDrawn){
        if (!customIsolines.isEmpty()){
            double value = customIsolines.constLast();
            for(int j = 0; j < m; j++){
                for(int i = 0; i < k; i++){
                    const ParametrsIsoline& params = ParametrsIsoline(this, i,j);
                    drawIsoline(params, value);
                }
            }
        }
        isLastIsolineDrawn = true;
    }
}

void Zone::drawIsoline(const ParametrsIsoline &params, const double value)
{
    bool sign[5];
    bool intersection[4] = {false};
    std::pair<double, double> point[4];
    sign[0] = params.f1 > value;
    sign[1] = params.f2 > value;
    sign[2] = params.f3 > value;
    sign[3] = params.f4 > value;
    double EPS = 0.0000001;
    int count = 0;
    if (sign[0] != sign[1]){
        intersection[0] = true;
        double x = params.xi + params.dx*((value - params.f1)/(params.f2 - params.f1 + EPS));
        point[0] = std::pair<double, double>(x, params.yj1);
        count++;
    }
    if (sign[2] != sign[3]){
        intersection[2] = true;
        double x = params.xi + params.dx*((value - params.f3)/(params.f4 - params.f3 + EPS));
        point[2] = std::pair<double, double>(x, params.yj);
        count++;
    }
    if (sign[0] != sign[2]){
        intersection[3] = true;
        double y = params.yj + params.dy*((value - params.f3)/(params.f1 - params.f3 + EPS));
        point[3] = std::pair<double, double>(params.xi, y);
        count++;
    }
    if (sign[1] != sign[3]){
        intersection[1] = true;
        double y = params.yj + params.dy*((value - params.f4)/(params.f2 - params.f4 + EPS));
        point[1] = std::pair<double, double>(params.xi1, y);
        count++;
    }
    if (count == 2){
        if (intersection[0] && intersection[1]){
            drawLine(pixelFromCoord(point[0]), pixelFromCoord(point[1]));
        } else if (intersection[0] && intersection[2]){
            drawLine(pixelFromCoord(point[0]), pixelFromCoord(point[2]));
        } else if (intersection[0] && intersection[3]){
            drawLine(pixelFromCoord(point[0]), pixelFromCoord(point[3]));
        } else if (intersection[1] && intersection[2]){
            drawLine(pixelFromCoord(point[1]), pixelFromCoord(point[2]));
        } else if (intersection[1] && intersection[3]){
            drawLine(pixelFromCoord(point[1]), pixelFromCoord(point[3]));
        } else if (intersection[2] && intersection[3]){
            drawLine(pixelFromCoord(point[2]), pixelFromCoord(point[3]));
        }
    }
    if (count == 4){
        //middle point
        sign[4] = function((params.xi + params.xi1)/2, (params.yj + params.yj1)/2) > value;
        if(sign[0] == sign[4]){
            drawLine(pixelFromCoord(point[0]), pixelFromCoord(point[1]));
            drawLine(pixelFromCoord(point[2]), pixelFromCoord(point[3]));
        } else {
            drawLine(pixelFromCoord(point[0]), pixelFromCoord(point[3]));
            drawLine(pixelFromCoord(point[1]), pixelFromCoord(point[2]));
        }
    }
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
    reset();
}

void Zone::initLegend()
{
    if (legend == nullptr){
        return;
    }
    legend->setN(n);
    legend->setColors(&colors);
}

QPoint Zone::pixelFromCoord(std::pair<double, double>& coord)
{
    double x = coord.first;
    double y = coord.second;
    return QPoint((x - a)*width/(b - a), height - (y - c)*height/(d - c));
}

std::pair<double, double> Zone::coordFromPixel(int i, int j)
{
    double x = (double)(b-a)*i/width + a;
    double y = (double)(d-c)*(height - j)/height + c;
    return std::pair<double, double>(x,y);
}

void Zone::reset()
{
    isMapDrawn = false;
    isGridDrawn = false;
    isIsolineDrawn = false;
    isLastIsolineDrawn = false;
}

void Zone::drawLine(QPoint point1, QPoint point2)
{
    int dx = std::abs(point1.x() - point2.x());
    int dy = std::abs(point1.y() - point2.y());
    if (dx > dy){
        drawLineX(point1, point2);
    } else {
        drawLineY(point1, point2);
    }
}

void Zone::drawLineX(QPoint point1, QPoint point2)
{
    if (point1.x() > point2.x()){
        std::swap(point1, point2);
    }

    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int width = image->bytesPerLine() / sizeof(QRgb);

    int dy = point2.y() - point1.y();
    int dx = point2.x() - point1.x();
    int sign = 1;
    if (dy < 0){
        dy *= -1;
        sign = -1;
    }
    int error = 0;
    int y = point1.y();
    int x = point1.x();

    for(int i = 0; i <= dx; i++){
        pixels[x + y*width] = lineColor;
        x++;
        error += dy;
        if (2*error > dx){
            error -= dx;
            y += sign;
        }
    }
}

void Zone::drawLineY(QPoint point1, QPoint point2)
{
    if (point1.y() > point2.y()){
        std::swap(point1, point2);
    }

    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int width = image->bytesPerLine() / sizeof(QRgb);

    int dx = point2.x() - point1.x();
    int dy = point2.y() - point1.y();
    int sign = 1;
    if (dx < 0){
        dx *= -1;
        sign = -1;
    }
    int error = 0;
    int x = point1.x();
    int y = point1.y();

    for(int i = 0; i <= dy; i++){
        pixels[x + y*width] = lineColor;
        y++;
        error += dx;
        if (2*error > dy){
            error -= dy;
            x += sign;
        }
    }
}

ParametrsIsoline::ParametrsIsoline(Zone* zone, int i, int j)
{
    double a = zone->a;
    double b = zone->b;
    double c = zone->c;
    double d = zone->d;
    int k = zone->k;
    int m = zone->m;
    this->xi = (b-a)*i/k + a;
    this->yj = (d-c)*j/m + c;
    this->xi1 = (b-a)*(i+1)/k + a;
    this->yj1 = (d-c)*(j+1)/m + c;
    this->f1 = zone->function(xi, yj1);
    this->f2 = zone->function(xi1, yj1);
    this->f3 = zone->function(xi, yj);
    this->f4 = zone->function(xi1, yj);
    this->dx = xi1 - xi;
    this->dy = yj1 - yj;
}
