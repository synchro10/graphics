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

    void update();
    void defaultSettings();
    QVector3D position;
    QVector3D rotation;
    float globalScale = 1.0f;
    QVector3D scale;
    QMatrix4x4 worldTransform;
    WireModel getWireModel() const;
    void setWireModel(const WireModel &value);

private:
    void calcWorldTransform();
    WireModel wireModel;
};

#endif // OBJECT_H
