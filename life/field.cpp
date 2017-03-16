#include "field.h"
#include <QRgb>
#include <QtWidgets>
#include <iostream>


Field::Field(QWidget *parent) : QWidget(parent)
{
    lineColor = qRgb(0,0,0);
    cellColor = qRgb(10,255,10);
    fontColor = qRgb(255,255,255);
    textColor = qRgb(10,10,200);
    image = new QImage(DEFAULT_WIDTH, DEFAULT_HEIGHT, QImage::Format_RGB32);
    image->fill(fontColor);

    resize(QSize(DEFAULT_WIDTH, DEFAULT_HEIGHT));
}

Field::~Field(){
    if (image != nullptr){
        delete image;
    }
}

void Field::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();

    drawGrid();

    painter.drawImage(dirtyRect, *image, dirtyRect);
    if (isShowImpact){
        drawImpacts(painter);
    }
}

void Field::drawLine(QPoint point1, QPoint point2)
{
    clippingLine(&point1, &point2);
    int dx = std::abs(point1.x() - point2.x());
    int dy = std::abs(point1.y() - point2.y());
    if (dx > dy){
        drawLineX(point1, point2);
    } else {
        drawLineY(point1, point2);
    }
}

void Field::changeParam(uint width, uint height, uint cell)
{
    if (width*height*cell == 0){
        return;
    }
    setGridWidth(width);
    setGridHeight(height);
    setCellSize(cell);

    int x = (cell*sqrt(3)) * (width);
    int y  = (3*cell/2 + cell % 2) * (height + 1 ) ;

    delete image;
    image = new QImage(x,y, QImage::Format_RGB32);
    image->fill(fontColor);
    resize(QSize(x, y));
}

void Field::clippingLine(QPoint *point1, QPoint *point2)
{
    //unsafe
}

void Field::drawLineX(QPoint point1, QPoint point2)
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

void Field::drawLineY(QPoint point1, QPoint point2)
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

QPoint Field::getCellByClick(int i, int j)
{
    int rsin30 = cellSize/2;
    int rcos30 = cellSize*sqrt(3)/2;

    int x0 , y0;
    int y = j / (2 * cellSize - rsin30);
    y0 = y * (2 * cellSize - rsin30);
    int x = 0;

    if (y & 0u == 0){
        x = (i - rcos30)/(2*rcos30);
        x0 = 2 * x * rcos30 + rcos30;
    } else {
         x = i/(2*rcos30);
         x0 = 2 * x * rcos30;
    }

    if (j < y0 + rsin30){
        if (i < x0 + rcos30){
            int dy = j - y0;
            int dx = x0 + rcos30 - i;
            if (dy*rcos30 <= dx*rsin30){
                x = x - (y+1)%2;
                y--;
            }
        } else {
            int dy = j - y0;
            int dx = i - x0 - rcos30;
            if (dy*rcos30 <= dx*rsin30){
                x = x + y%2;
                y--;
            }
        }
    }
    return QPoint(x,y);
}

void Field::drawImpacts(QPainter &painter)
{
    if (cellSize < 17){
        return;
    }
    painter.setPen(textColor);

    int rsin30 = cellSize/2;
    int rcos30 = cellSize*sqrt(3)/2;

    for(uint y = 0; y < gridHeight; y++){
        uint width = gridWidth - y%2;
        for(uint x = 0; x < width; x++){
            int y0 = y * (2 * cellSize - rsin30);
            int x0 = 0;
            if (y & 0u == 0u){
                x0 = 2 * x * rcos30 + 2*rcos30;
            } else {
                 x0 = 2 * x * rcos30 + rcos30;
            }
            y0 += cellSize;
            y0 += cellSize/6;
            uint impact = model->getImpact(x,y);
            double impact_ = (double)impact/10;
            QString text = QString::number(impact_);
            x0 -= 3*text.length();
            painter.drawText(x0,y0,text);
        }
    }
}

void Field::setModel(Model *value)
{
    model = value;
}

uint Field::getGridWidth() const
{
    return gridWidth;
}

void Field::setGridWidth(const uint &value)
{
    gridWidth = value;
}

void Field::drawHexagon(uint x, uint y)
{
    if (x > gridWidth || y > gridHeight){
        return;
    }

    int rsin30 = cellSize/2;
    int rcos30 = cellSize*sqrt(3)/2;

    int y0 = y * (2 * cellSize - rsin30);
    int x0 = 0;
    if (y & 0u == 0){
        x0 = 2 * x * rcos30 + rcos30;
    } else {
         x0 = 2 * x * rcos30;
    }

    QPoint point1 = QPoint(x0,              y0 + rsin30);
    QPoint point2 = QPoint(x0 + rcos30,     y0 );
    QPoint point3 = QPoint(x0 + 2*rcos30,   y0 + rsin30);
    QPoint point4 = QPoint(x0 + 2*rcos30,   y0 + 2*cellSize - rsin30);
    QPoint point5 = QPoint(x0 + rcos30,     y0 + 2*cellSize);
    QPoint point6 = QPoint(x0,              y0 + 2*cellSize - rsin30);

    drawLine(point1, point2);
    drawLine(point2, point3);
    drawLine(point1, point6);
    drawLine(point3, point4);
    drawLine(point6, point5);
    drawLine(point5, point4);
}

void Field::drawGrid()
{
    for(uint i = 0; i < gridHeight; i++){
        uint width = gridWidth - i%2;
        for(uint j = 0; j < width; j++){
            drawHexagon(j, i);
            if (field != nullptr){
                if ((*field)[i][j]){
                    fillCell(j,i,cellColor);
                } else {
                    fillCell(j,i,fontColor);
                }
            }
        }
    }
}


void Field::fillCell(uint x, uint y, QRgb color)
{
    if (x > gridWidth || y > gridHeight){
        return;
    }

    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int width = image->bytesPerLine() / sizeof(QRgb);

    int rsin30 = cellSize/2;
    int rcos30 = cellSize*sqrt(3)/2;

    int y0 = y * (2 * cellSize - rsin30);
    int y1 = y0 + 2 * cellSize;
    int x0 = 0;
    if (y & 0u == 0u){
        x0 = 2 * x * rcos30 + 2*rcos30;
    } else {
         x0 = 2 * x * rcos30 + rcos30;
    }

    for(int i = y0; i < y1; i++){
        for(int j = x0; j < x0 + rcos30; j++){
            if (pixels[i * width + j] == lineColor){
                break;
            }
            pixels[i * width + j] = color;
        }
        for(int j = x0; j > x0 - rcos30; j--){
            if (pixels[i * width + j] == lineColor){
                break;
            }
            pixels[i * width + j] = color;
        }
    }
}

void Field::setField(std::vector<std::vector<bool> > *_field)
{
    field = _field;
}

void Field::init()
{
    field = &(model->getCurrentState());
    impact = &(model->getImpact());
}

void Field::mousePressEvent(QMouseEvent *e)
{
    int i = e->x();
    int j = e->y();

    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int width = image->bytesPerLine() / sizeof(QRgb);
    if (pixels[width*j + i] == lineColor){
        return;
    }

    QPoint cell = getCellByClick(i, j);
    int x = cell.x();
    int y = cell.y();

    if (x < 0 || x >= gridWidth || y < 0 || y >= gridHeight){
        return;
    }

    lastPoint = cell;

    if (isXOR){
        model->invertCell(x,y);
    } else {
        model->aliveCell(x,y);
    }
    model->countNextState();
    update();
}

void Field::mouseMoveEvent(QMouseEvent *e)
{
    int i = e->x();
    int j = e->y();

    QRgb* pixels = reinterpret_cast<QRgb*>(image->bits());
    int width = image->bytesPerLine() / sizeof(QRgb);
    if (pixels[width*j + i] == lineColor){
        return;
    }

    QPoint cell = getCellByClick(i, j);

    int x = cell.x();
    int y = cell.y();

    if (x < 0 || x >= gridWidth || y < 0 || y >= gridHeight){
        return;
    }
    if (cell == lastPoint){
        return;
    } else {
        lastPoint = cell;
    }

    if (isXOR){
        model->invertCell(x,y);
    } else {
        model->aliveCell(x,y);
    }
    model->countNextState();
    update();
}

uint Field::getGridHeight() const
{
    return gridHeight;
}

void Field::setGridHeight(const uint &value)
{
    gridHeight = value;
}

uint Field::getCellSize() const
{
    return cellSize;
}

void Field::setCellSize(const uint &value)
{
    cellSize = value;
}


