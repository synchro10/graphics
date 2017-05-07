#ifndef GRAPHICENGINE_H
#define GRAPHICENGINE_H

#include "camera.h"
#include "object.h"
#include <QVector>
#include <QImage>
#include <QtMath>
#include <QSharedPointer>
#include <iostream>
#include "graphics2d.h"

class GraphicEngine
{
public:
    GraphicEngine();
    QImage& render();
private:
    Camera camera;
    QVector<Object> objects;
    QImage frame;

    int width = 800;
    int height = 600;
    bool zClipping(QVector3D &p1, QVector3D &p2);
};

#endif // GRAPHICENGINE_H
