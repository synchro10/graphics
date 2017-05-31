#ifndef OBJECT_H
#define OBJECT_H

#include "wire/wiremodel.h"
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
    void update();
    void defaultSettings();
    QVector3D position;
    QVector3D rotation;
    QVector3D scaling;
    QMatrix4x4 worldTransform;
    WireModel getWireModel() const;
    void setWireModel(const WireModel &value);

private:
    void calcWorldTransform();
    WireModel wireModel;
    float globalScale = 1.0f;
    QMatrix4x4 scaleMatrix;
    QMatrix4x4 rotateMatrix;
    QMatrix4x4 translationMatrix;
};

#endif // OBJECT_H
