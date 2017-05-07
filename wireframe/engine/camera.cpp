#include "camera.h"

Camera::Camera()
{

}

void Camera::defaultSettings()
{
    position = QVector3D(-10, 0, 0);
    rotation = QVector3D(0, 0, 0);
    scale = QVector3D(1, 1, 1);
    height = 600;
    width = 800;
    nearPlane = 0.1;
    farPlane = 50;
}

QMatrix4x4 Camera::getViewTransform() const
{
    return viewTransform;
}

QMatrix4x4 Camera::getProjectionTransform() const
{
    return projectionTransform;
}

void Camera::update()
{
    calcViewTransform();
    calcProjectionTransform();
}

void Camera::calcViewTransform()
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
    viewTransform = scaleMatrix * rotationMatrix * translationMatrix;
}

void Camera::calcProjectionTransform()
{
    float w = (float)2*nearPlane/width;
    float h = (float)2*nearPlane/height;
    float Q = (float)farPlane/(farPlane - nearPlane);

    projectionTransform = QMatrix4x4(w, 0, 0, 0,
                                     0, h, 0, 0,
                                     0, 0, Q, 1,
                                     0, 0, -Q*nearPlane, 0);
}
