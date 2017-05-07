#include "object.h"

Object::Object()
{
    defaultSettings();
}

void Object::defaultSettings()
{
    position = QVector3D(0, 0, 0);
    rotation = QVector3D(0, 0, 0);
    scale = QVector3D(1, 1, 1);
    update();
}

void Object::update()
{
    calcWorldTransform();
}

void Object::calcWorldTransform()
{
    QMatrix4x4 scaleMatrix = QMatrix4x4(scale.x(), 0, 0, 0,
                                        0, scale.y(), 0, 0,
                                        0, 0, scale.z(), 0,
                                        0, 0, 0, 1);
    QMatrix4x4 translationMatrix = QMatrix4x4(1, 0, 0, 0,
                                              0, 1, 0, 0,
                                              0, 0, 1, 0,
                                              position.x(), position.y(), position.z(), 1);
    QMatrix4x4 rotationMatrix = QMatrix4x4();
    float phi = rotation.x();
    QMatrix4x4 rotationX = QMatrix4x4(1, 0, 0, 0,
                                      0, qCos(phi), qSin(phi), 0,
                                      0, -1*qSin(phi), qCos(phi), 0,
                                      0, 0, 0, 1);
    phi = rotation.y();
    QMatrix4x4 rotationY = QMatrix4x4(qCos(phi), 0, -1*qSin(phi), 0,
                                      0, 1, 0, 0,
                                      qSin(phi), 0, qCos(phi), 0,
                                      0, 0, 0, 1);
    phi = rotation.z();
    QMatrix4x4 rotationZ = QMatrix4x4(qCos(phi), qSin(phi), 0, 0,
                                      -1*qSin(phi), qCos(phi), 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1);
    rotationMatrix = rotationY * rotationX * rotationZ;

    //todo test
    worldTransform = scaleMatrix * rotationMatrix * translationMatrix;
}

WireModel Object::getWireModel() const
{
    return wireModel;
}
