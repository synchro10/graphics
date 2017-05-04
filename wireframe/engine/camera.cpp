#include "camera.h"

Camera::Camera()
{

}

void Camera::defaultSettings()
{
    position = QVector3D(-10, 0, 0);
    rotation = QVector3D(0, 0, 0);
    scale = QVector3D(1, 1, 1);
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

}
