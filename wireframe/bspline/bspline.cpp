#include "bspline.h"
#include <assert.h>

BSpline::BSpline()
{
}

void BSpline::defaultInit()
{

}

void BSpline::addPoint(float x, float y)
{
    referencePoints.push_back(QPointF(x,y));
    ++N;
}

void BSpline::createValues()
{
    values.clear();
    length = 0.0f;
    const int parts = 100;
    for(int i = 2; i <= N - 2; i++){
        for(int j = 0; j <= parts; j++){
            QPointF v = value(i, (float)j/parts);
            if(!values.isEmpty()){
                length += countLength(v, values.last());
            }
            values.push_back(v);
        }
    }
    findMaxValue();
}

int BSpline::getN() const
{
    return N;
}

QVector<QPointF> BSpline::getReferencePoints() const
{
    return referencePoints;
}

QVector<QPointF> BSpline::getPoints(const int count, const float a, const float b)
{
    assert(0.0f <= a && a < b && b <= 1.0f);
    const float lengthA = (this->length) * a;
    const float lengthB = (this->length) * (1 - b);
    const float length = (this->length)*(b - a)/count;
    float curLength = 0.0f;
    int i = 0;
    float nextPartLength = countLength(values[i], values[i+1]);
    QVector<QPointF> points = QVector<QPointF>();

    //find first point equal to u0 = a
    while(qAbs(lengthA - curLength) >= qAbs(curLength + nextPartLength - lengthA)){
        i++;
        curLength += nextPartLength;
        nextPartLength = countLength(values[i], values[i+1]);
    }
    points.push_back(values[i]);

    //find points equl to u1 ... un-1
    curLength = 0.0f;
    for(++i; i < values.size() - 1; i++){
        curLength += countLength(values[i - 1], values[i]);
        nextPartLength = countLength(values[i], values[i+1]);
        if (qAbs(length - curLength) < qAbs(curLength + nextPartLength - length)){
            points.push_back(values[i]);
            curLength = 0.0f;
            if(points.size() == count){
                break;
            }
        }
    }

    //find last point equal to un = b
    i = values.size() - 1;
    curLength = 0.0f;
    nextPartLength = countLength(values[i], values[i-1]);
    while(qAbs(lengthB - curLength) >= qAbs(curLength + nextPartLength - lengthB)){
        i--;
        curLength += nextPartLength;
        nextPartLength = countLength(values[i], values[i-1]);
    }
    points.push_back(values[i]);

    return points;
}

QVector4D BSpline::T(const float t)
{
    return QVector4D(t*t*t, t*t, t, 1);
}

QVector4D BSpline::Gx(const int i)
{
    if (i < 2 || i > N - 2){
        return QVector4D(0, 0, 0, 0);
    } else {
        return QVector4D(referencePoints[i - 2].x(), referencePoints[i - 1].x(),
                         referencePoints[i].x(), referencePoints[i + 1].x());
    }
}

QVector4D BSpline::Gy(const int i)
{
    if (i < 2 || i > N - 2){
        return QVector4D(0, 0, 0, 0);
    } else {
        return QVector4D(referencePoints[i - 2].y(), referencePoints[i - 1].y(),
                         referencePoints[i].y(), referencePoints[i + 1].y());
    }
}

QPointF BSpline::value(const int segment, const float param)
{
    QVector4D Tv = T(param);
    float x = QVector4D::dotProduct(Tv*Ms, Gx(segment));
    float y = QVector4D::dotProduct(Tv*Ms, Gy(segment));
    return QPointF(x, y);
}

float BSpline::countLength(const QPointF &p1, const QPointF &p2)
{
    return qSqrt((p1.x() - p2.x())*(p1.x() - p2.x()) + (p1.y() - p2.y())*(p1.y() - p2.y()));
}



void BSpline::drawBSpine(QImage *image)
{
    int height = image->height();
    int width = image->width();
    Graphics2D::fill(*image, qRgb(255,255,255));
    Graphics2D::drawLine(QPoint(0, height/2), QPoint(width, height/2), qRgb(0,0,0), *image);
    Graphics2D::drawLine(QPoint(width/2, 0), QPoint(width/2, height), qRgb(0,0,0), *image);
    for(int i = 0; i < values.size() - 1; i++){
        auto pix1 = pointToPix(values[i], height, width);
        auto pix2 = pointToPix(values[i+1], height, width);
        Graphics2D::drawLine(pix1, pix2, qRgb(0,0,0), *image);
    }
    for(auto& point: referencePoints){
        Graphics2D::drawPixel(*image, pointToPix(point, height, width), qRgb(255,0,0));
    }
}

void BSpline::findMaxValue()
{
    float max = 0.0f;
    for(QPointF& point: values){
        max = std::max(max, float(std::max(qAbs(point.x()), qAbs(point.y()))));
    }
    maxValue = max;
}

QPoint BSpline::pointToPix(const QPointF& point, const int height, const int width)
{
    float a = -maxValue  * 1.3f;
    float b = maxValue   * 1.3f;
    float c = -maxValue  * 1.3f;
    float d = maxValue   * 1.3f;
    float x = point.x();
    float y = point.y();
    return QPoint((x - a)*(width-1)/(b - a), (height-1) - (y - c)*(height-1)/(d - c));
}
