#ifndef BSPLINE_H
#define BSPLINE_H

#include <QVector>
#include <QPoint>
#include <QVector4D>
#include <QMatrix4x4>
#include <QtMath>
#include <QPointF>
#include <QImage>
#include "../engine/graphics2d.h"
#include "settings.h"

class BSpline
{
public:
    BSpline();
    Settings settings = Settings();
    void defaultInit();
    void addPoint(float x, float y);
    void createValues();

    int getN() const;
    QVector<QPointF> getReferencePoints() const;
    QVector<QPointF> getPoints(const int count, const float a, const float b);
    void drawBSpine(QImage* image);

private:
    QVector<QPointF> referencePoints = QVector<QPointF>();
    int N = 0;
    float length = 0.0f;
    QMatrix4x4 Ms = QMatrix4x4(-1, 3, -3, 1,
                               3, -6, 3, 0,
                               -3, 0, 3, 0,
                               1, 4, 1, 0) / 6;
    QVector4D T(const float t);
    QVector4D Gx(const int i);
    QVector4D Gy(const int i);
    QVector<QPointF> values = QVector<QPointF>();
    QPointF value(const int segment, const float param);
    float countLength(const QPointF& p1, const QPointF& p2);
    QPoint pointToPix(const QPointF &point, const int height, const int width);
};

#endif // BSPLINE_H
