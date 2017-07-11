#include "zone.h"
#include <iostream>
#include <qmath.h>

Zone::Zone(QWidget *parent) : QWidget(parent)
{
    setFixedSize(width + 20, height + 20);
    image = QSharedPointer<QImage>(new QImage(width, height, QImage::Format_RGB32));
    values = QVector<double>();
    customIsolines = QVector<double>();
    colors = QVector<QRgb>();
    defaultParams();
    setMouseTracking(true);
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
//    setFunction([](double x,double y){return x*x + y*y;});
    setFunction([](double x,double y){return sin(x*y);});
    k = 5;
    m = 5;
    a = -1.0;
    c = -1.0;
    b = 1.0;
    d = 1.0;
    n = 4;
    colors.clear();
    for (int i = 0; i <= n; i++){
        colors.push_back(qRgb(0,255*(n-i)/n,0));
//        std::cout << 0 << " " << 255*(n-i)/n << " " << 0 << std::endl;
    }
    setIsolineColor(qRgb(255,255,255));
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

void Zone::setPoint()
{
    isPoint = !isPoint;
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

void Zone::setIsolineColor(QRgb color)
{
    lineColor = color;
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
        updateValues();
        initLegend();
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
        if (e->buttons() == Qt::LeftButton){
            if (!customIsolines.isEmpty()){
                customIsolines.removeLast();
                reset();
            }
            mousePressEvent(e);
        }
        emit(statusMessage(getStatus(e)));
    }
}

QString Zone::getStatus(QMouseEvent *e)
{
    auto coord = coordFromPixel(e->x(), e->y());
    double value = function(coord.first, coord.second);
    QString message = QString();
    message += "x = " + QString::number(coord.first, 'f',3);
    message += " y = " + QString::number(coord.second, 'f',3);
    message += " f = " + QString::number(value, 'f',3);
    return message;
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
    Coordinate point[4];
    sign[0] = params.f1 > value;
    sign[1] = params.f2 > value;
    sign[2] = params.f3 > value;
    sign[3] = params.f4 > value;
    double EPS = 0.0000001;
    int count = 0;
    if (sign[0] != sign[1]){
        intersection[0] = true;
        double x = params.xi;
        if (qFabs(value - params.f1) > EPS && qFabs(params.f2 - params.f1) > EPS){
            x += params.dx*(qFabs(value - params.f1)/qFabs(params.f2 - params.f1  ));
        } else {
            x += params.dx/2;
        }
        x = x < params.xi ? params.xi : x > params.xi1 ? params.xi1 : x;
        point[0] = Coordinate(x, params.yj1);
        count++;
    }
    if (sign[2] != sign[3]){
        intersection[2] = true;
        double x = params.xi;
        if (qFabs(value - params.f3) > EPS && qFabs(params.f4 - params.f3) > EPS){
            x+= params.dx*(qFabs(value - params.f3)/qFabs(params.f4 - params.f3  ));
        } else {
            x += params.dx/2;
        }
        x = x < params.xi ? params.xi : x > params.xi1 ? params.xi1 : x;
        point[2] = Coordinate(x, params.yj);
        count++;
    }
    if (sign[0] != sign[2]){
        intersection[3] = true;
        double y = params.yj;
        if (qFabs(value - params.f3) > EPS && qFabs(params.f1 - params.f3) > EPS){
            y += params.dy*(qFabs(value - params.f3)/qFabs(params.f1 - params.f3  ));
        } else {
            y += params.dy/2;
        }
        y = y < params.yj ? params.yj : y > params.yj1 ? params.yj1 : y;
        point[3] = Coordinate(params.xi, y);
        count++;
    }
    if (sign[1] != sign[3]){
        intersection[1] = true;
        double y = params.yj;
        if (qFabs(value - params.f4) > EPS && qFabs(params.f2 - params.f4) > EPS){
            y += params.dy*(qFabs(value - params.f4)/qFabs(params.f2 - params.f4  ));
        } else {
            y += params.dy/2;
        }
        y = y < params.yj ? params.yj : y > params.yj1 ? params.yj1 : y;
        point[1] = Coordinate(params.xi1, y);
        count++;
    }
    if (count == 2){
        if (intersection[0] && intersection[1]){
            drawLinePoint(pixelFromCoord(point[0]), pixelFromCoord(point[1]));
        } else if (intersection[0] && intersection[2]){
            drawLinePoint(pixelFromCoord(point[0]), pixelFromCoord(point[2]));
        } else if (intersection[0] && intersection[3]){
            drawLinePoint(pixelFromCoord(point[0]), pixelFromCoord(point[3]));
        } else if (intersection[1] && intersection[2]){
            drawLinePoint(pixelFromCoord(point[1]), pixelFromCoord(point[2]));
        } else if (intersection[1] && intersection[3]){
            drawLinePoint(pixelFromCoord(point[1]), pixelFromCoord(point[3]));
        } else if (intersection[2] && intersection[3]){
            drawLinePoint(pixelFromCoord(point[2]), pixelFromCoord(point[3]));
        }
    }
    if (count == 4){
        //middle point
        double f5 = function((params.xi + params.xi1)/2, (params.yj + params.yj1)/2);
        sign[4] = f5 > value;
        double x = 0.0;
        double y = 0.0;
        const double dx = params.dx/2;
        const double dy = params.dy/2;
        if(sign[0] == sign[4]){
            //point between 2 edge and 3 edge
            x = params.xi;
            y = params.yj;
            if (qFabs(value - params.f3) > EPS && qFabs(f5 - params.f3) > EPS){
                x += dx*(qFabs(value - params.f3)/qFabs(f5 - params.f3  ));
                y += dy*(qFabs(value - params.f3)/qFabs(f5 - params.f3  ));
            } else {
                x += dx/2;
                y += dy/2;
            }
            x = x < params.xi ? params.xi : x > params.xi + dx ? params.xi + dx : x;
            y = y < params.yj ? params.yj : y > params.yj + dy ? params.yj + dy : y;

            Coordinate point23 = Coordinate(x, y);

            //point between 0 edge and 1 edge
            x = params.xi + dx;
            y = params.yj + dy;
            if (qFabs(value - f5) > EPS && qFabs(params.f2 - f5) > EPS){
                x += dx*(qFabs(value - f5)/qFabs(params.f2 - f5  ));
                y += dy*(qFabs(value - f5)/qFabs(params.f2 - f5  ));
            } else {
                x += dx/2;
                y += dy/2;
            }
            x = x < params.xi + dx ? params.xi + dx: x > params.xi1 ? params.xi1 : x;
            y = y < params.yj1 - dy ? params.yj1 - dy : y > params.yj1 ? params.yj1 : y;

            Coordinate point01 = Coordinate(x, y);

            drawLinePoint(pixelFromCoord(point[0]), pixelFromCoord(point01));
            drawLinePoint(pixelFromCoord(point01), pixelFromCoord(point[1]));
            drawLinePoint(pixelFromCoord(point[2]), pixelFromCoord(point23));
            drawLinePoint(pixelFromCoord(point23), pixelFromCoord(point[3]));

        } else {
            // point between 1 edge and 2 edge
            x = params.xi + dx;
            y = params.yj + dy;
            if (qFabs(value - f5) > EPS && qFabs(f5 - params.f4) > EPS){
                x += dx*(qFabs(value - f5)/qFabs(f5 - params.f4  ));
                y -= dy*(qFabs(value - f5)/qFabs(f5 - params.f4  ));
            } else {
                x += dx/2;
                y -= dy/2;
            }
            x = x < params.xi + dx ? params.xi + dx : x > params.xi1 ? params.xi1 : x;
            y = y < params.yj ? params.yj : y > params.yj + dy ? params.yj + dy : y;

            Coordinate point12 = Coordinate(x, y);

            // point between 0 edge and 3 edge
            x = params.xi;
            y = params.yj1;
            if (qFabs(value - params.f1) > EPS && qFabs(params.f1 - f5) > EPS){
                x += dx*(qFabs(value - params.f1)/qFabs(params.f1 - f5  ));
                y -= dy*(qFabs(value - params.f1)/qFabs(params.f1 - f5  ));
            } else {
                x += dx/2;
                y -= dy/2;
            }
            x = x < params.xi ? params.xi : x > params.xi + dx ? params.xi + dx : x;
            y = y < params.yj + dy ? params.yj + dy : y > params.yj1 ? params.yj1 : y;

            Coordinate point03 = Coordinate(x, y);

            drawLinePoint(pixelFromCoord(point[0]), pixelFromCoord(point03));
            drawLinePoint(pixelFromCoord(point03), pixelFromCoord(point[3]));
            drawLinePoint(pixelFromCoord(point[1]), pixelFromCoord(point12));
            drawLinePoint(pixelFromCoord(point12), pixelFromCoord(point[2]));

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
    this->clearIsolines();
    initLegend();
    reset();
}

void Zone::initLegend()
{
    if (legend == nullptr){
        return;
    }
    legend->init(n, colors, values);
}

QPoint Zone::pixelFromCoord(Coordinate& coord)
{
    double x = coord.first;
    double y = coord.second;
    return QPoint((x - a)*(width-1)/(b - a), (height-1) - (y - c)*(height-1)/(d - c));
}

Coordinate Zone::coordFromPixel(int i, int j)
{
    double x = (double)(b-a)*i/(width-1) + a;
    double y = (double)(d-c)*(height-1 - j)/(height-1) + c;
    return Coordinate(x,y);
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

void Zone::drawLinePoint(QPoint point1, QPoint point2)
{
    if (isPoint){
        drawPoint3(point1);
        drawPoint3(point2);
    }
    drawLine(point1, point2);
}

void Zone::drawPoint3(QPoint point)
{
    int x = point.x();
    int y = point.y();
    if (0 < x && x < width - 1 && 0 < y && y < height - 1){
        QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
        int pixPerLine = image->bytesPerLine() / sizeof(QRgb);
        for(int j = -1; j <= 1; j++){
            for(int i = -1; i <= 1; i++){
                pixels[x + i + (y+j)*pixPerLine] = lineColor;
            }
        }
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
