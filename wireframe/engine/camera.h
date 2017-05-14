#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>
#include <QtMath>

class Camera
{
public:
    Camera();
    void defaultSettings();
    QMatrix4x4 getViewTransform() const;
    QMatrix4x4 getProjectionTransform() const;

    QVector3D position;
    QVector3D rotation;
    QVector3D scale;
    //fov in radians
    float fovX;
    float fovY;
    float height;
    float width;
    float nearPlane;
    float farPlane;
    float aspect;
    QMatrix4x4 viewTransform;
    QMatrix4x4 projectionTransform;
private:
    void update();
    void calcViewTransform();
    void calcProjectionTransform();
};

#endif // CAMERA_H
