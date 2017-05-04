#ifndef CAMERA_H
#define CAMERA_H

#include <QVector3D>
#include <QVector4D>
#include <QMatrix4x4>

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
    uint fov;
    uint height;
    uint width;
    float nearPlane;
    float farPlane;
    QMatrix4x4 viewTransform;
    QMatrix4x4 projectionTransform;
private:
    void update();
};

#endif // CAMERA_H
