#ifndef OBJECT_H
#define OBJECT_H

#include "wire/wiremodel.h"
#include "bspline/bspline.h"
#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <QtMath>

class Object
{
public:
    Object();

    void rotate(float angleX, float angleY, float angleZ);
    void scale(float scaleX, float scaleY, float scaleZ);
    void scale(float scale);
    void move(float dx, float dy, float dz);
    void moveTo(float x, float y, float z);
    void update();
    void defaultSettings();

    WireModel getWireModel() const;
    void setWireModel(const WireModel &value);
    QMatrix4x4 getWorldTransform() const;
    BSpline getBSpline() const;
    void setBSpline(const BSpline &value);

    QRgb getColor() const;
    void setColor(const QRgb &value);

private:
    void calcWorldTransform();
    WireModel wireModel;
    BSpline bSpline;
    float globalScale = 1.0f;
    QMatrix4x4 scaleMatrix;
    QMatrix4x4 rotateMatrix;
    QMatrix4x4 translationMatrix;
    QMatrix4x4 worldTransform;
    QVector3D position;
    QVector3D rotation;
    QVector3D scaling;
    QRgb color = qRgb(rand()%256, rand()%256, rand()%256);
};

#endif // OBJECT_H
