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
#include "settings.h"

class GraphicEngine
{
public:
    enum {
        SPLINE, WORLD
    };
    GraphicEngine();
    QImage *render();
    void setCamera(Camera& camera);
    void addObject(Object& object);
    void clear();
    void rotate(int dyPix, int dxPix);
    void scale(int y);
    void zoom(int y);
    void changeMode();
    bool isSplineMode();
    Settings getSettings() const;
    void setSettings(const Settings &value);
    void rotateScene(int dy, int dx);
    void reset();

    void setDefaultFontColor(const QRgb &value);

    void setGlobalRotate(const QMatrix4x4 &value);
    void nextFigure();
    void prevFigure();
private:
    Camera camera;
    QVector<Object> objects;
    QImage* frame;
    Settings settings = Settings();
    QMatrix4x4 globalRotate;
    QMatrix4x4 defaultRotate;
    int width = 800;
    int height = 600;
    const QRgb defaultLineColor = qRgb(255,255,255);
    QRgb defaultFontColor = qRgb(0,0,0);

    bool zClipping(QVector3D &p1, QVector3D &p2);
    QPoint pixFromCoord(const QVector3D &coord);
    int mode = WORLD;
    int currentObject = 0;
};



#endif // GRAPHICENGINE_H
