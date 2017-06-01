#include "object.h"

Object::Object()
{
    defaultSettings();
}

void Object::rotate(float angleX, float angleY, float angleZ)
{
    QMatrix4x4 rotationX = QMatrix4x4(1, 0, 0, 0,
                                      0, qCos(angleX), qSin(angleX), 0,
                                      0, -1*qSin(angleX), qCos(angleX), 0,
                                      0, 0, 0, 1);
    QMatrix4x4 rotationY = QMatrix4x4(qCos(angleY), 0, -1*qSin(angleY), 0,
                                      0, 1, 0, 0,
                                      qSin(angleY), 0, qCos(angleY), 0,
                                      0, 0, 0, 1);
    QMatrix4x4 rotationZ = QMatrix4x4(qCos(angleZ), qSin(angleZ), 0, 0,
                                      -1*qSin(angleZ), qCos(angleZ), 0, 0,
                                      0, 0, 1, 0,
                                      0, 0, 0, 1);
    QMatrix4x4 globalRotate = rotationY * rotationX * rotationZ;
    rotateMatrix *= globalRotate;
    update();
}

void Object::scale(float scaleX, float scaleY, float scaleZ)
{
    //todo
}

void Object::scale(float scale)
{
    float newScale = globalScale*scale;
    newScale = newScale > 5.0f ? 5.0f : newScale < 0.2f ? 0.2f : newScale;
    scaling *= (newScale/globalScale);
    globalScale = newScale;
    scaleMatrix = QMatrix4x4(scaling.x(), 0, 0, 0,
                            0, scaling.y(), 0, 0,
                            0, 0, scaling.z(), 0,
                            0, 0, 0, 1);
    update();
}

void Object::move(float dx, float dy, float dz)
{
    position -= QVector3D(dx, dy, dz);
    translationMatrix = QMatrix4x4(1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  position.x(), position.y(), position.z(), 1);
    update();
}

void Object::moveTo(float x, float y, float z)
{
    position = QVector3D(x, y, z);
    translationMatrix = QMatrix4x4(1, 0, 0, 0,
                                  0, 1, 0, 0,
                                  0, 0, 1, 0,
                                  position.x(), position.y(), position.z(), 1);
    update();
}

void Object::defaultSettings()
{
    {
        scaling = QVector3D(1, 1, 1);
        scaleMatrix = QMatrix4x4(scaling.x(), 0, 0, 0,
                                0, scaling.y(), 0, 0,
                                0, 0, scaling.z(), 0,
                                0, 0, 0, 1);
    }
    {
        position = QVector3D(0, 0, 0);
        translationMatrix = QMatrix4x4(1, 0, 0, 0,
                                      0, 1, 0, 0,
                                      0, 0, 1, 0,
                                      position.x(), position.y(), position.z(), 1);
    }
    {
        rotation = QVector3D(0, 0, 0);
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
        rotateMatrix = rotationY * rotationX * rotationZ;
    }
    update();
}

void Object::update()
{
    calcWorldTransform();
}

void Object::calcWorldTransform()
{
    worldTransform = scaleMatrix * rotateMatrix * translationMatrix;
}

QRgb Object::getColor() const
{
    return color;
}

void Object::setColor(const QRgb &value)
{
    color = value;
}

BSpline Object::getBSpline() const
{
    return bSpline;
}

void Object::setBSpline(const BSpline &value)
{
    bSpline = value;
}

QMatrix4x4 Object::getWorldTransform() const
{
    return worldTransform;
}

void Object::setWireModel(const WireModel &value)
{
    wireModel = value;
}

WireModel Object::getWireModel() const
{
    return wireModel;
}
