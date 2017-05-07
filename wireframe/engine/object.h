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

    void defaultSettings();
    QVector3D position;
    QVector3D rotation;
    QVector3D scale;
    QMatrix4x4 worldTransform;
    WireModel getWireModel() const;

private:
    void update();
    void calcWorldTransform();
    WireModel wireModel;
};

#endif // OBJECT_H
