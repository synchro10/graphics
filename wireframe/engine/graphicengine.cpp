#include "graphicengine.h"
#include "graphics2d.h"

GraphicEngine::GraphicEngine()
{
    globalRotate = QMatrix4x4(1, 0, 0, 0,
                              0, 1, 0, 0,
                              0, 0, 1, 0,
                              0, 0, 0, 1);
    defaultRotate = globalRotate;
}

QImage *GraphicEngine::render()
{
    frame = new QImage(width, height, QImage::Format_RGB32);
    if (mode == SPLINE){
        objects[currentObject].getBSpline().drawBSpine(frame);
    } else if (mode == WORLD){
        Graphics2D::fill(*frame, defaultFontColor);
        const QMatrix4x4& Mv = camera.getViewTransform();
        const QMatrix4x4& Mp = camera.getProjectionTransform();
        const QMatrix4x4& MvMp = Mv*Mp;
        for(const Object& object: objects){
            const auto& edges = object.getWireModel().getModel();
            const QMatrix4x4& Mw = object.getWorldTransform();
            const QRgb color = object.getColor();
            for(WireModel::Edge edge: edges){
                QVector4D p1 = QVector4D(edge.first, 1.0);
                QVector4D p2 = QVector4D(edge.second, 1.0);
                p1 = p1*(Mw*globalRotate*MvMp);
                p2 = p2*(Mw*globalRotate*MvMp);
                float w = p1.w();
                QVector3D positionScr1 = QVector3D(p1.x()/w, p1.y()/w, p1.z()/w);
                w = p2.w();
                QVector3D positionScr2 = QVector3D(p2.x()/w, p2.y()/w, p2.z()/w);
                if (zClipping(positionScr1, positionScr2)){
                    QPoint p1 = pixFromCoord(positionScr1);
                    QPoint p2 = pixFromCoord(positionScr2);
                    Graphics2D::drawLine(p1, p2, color, *frame);
                }
            }
            //draw coord oxes
            {
                float d = 0.5f;
                QRgb colorX = qRgb(255, 0, 0);
                QRgb colorY = qRgb(0, 255, 0);
                QRgb colorZ = qRgb(0, 0, 255);
                QVector4D p0 = QVector4D(0.0f, 0.0f, 0.0f, 1.0f);
                QVector4D px = QVector4D(d, 0.0f, 0.0f, 1.0f);
                QVector4D py = QVector4D(0.0f, d, 0.0f, 1.0f);
                QVector4D pz = QVector4D(0.0f, 0.0f, d, 1.0f);
                p0 = p0*Mw*globalRotate*MvMp;
                px = px*Mw*globalRotate*MvMp;
                py = py*Mw*globalRotate*MvMp;
                pz = pz*Mw*globalRotate*MvMp;
                QVector3D pScr0  = QVector3D(p0.x()/p0.w(), p0.y()/p0.w(), p0.z()/p0.w());
                QVector3D pScrX  = QVector3D(px.x()/p0.w(), px.y()/p0.w(), px.z()/px.w());
                QVector3D pScrY  = QVector3D(py.x()/p0.w(), py.y()/p0.w(), py.z()/py.w());
                QVector3D pScrZ  = QVector3D(pz.x()/p0.w(), pz.y()/p0.w(), pz.z()/pz.w());
                if (zClipping(pScr0, pScrX)){
                    Graphics2D::drawLine(pixFromCoord(pScr0), pixFromCoord(pScrX), colorX, *frame);
                }
                if (zClipping(pScr0, pScrY)){
                    Graphics2D::drawLine(pixFromCoord(pScr0), pixFromCoord(pScrY), colorY, *frame);
                }
                if (zClipping(pScr0, pScrZ)){
                    Graphics2D::drawLine(pixFromCoord(pScr0), pixFromCoord(pScrZ), colorZ, *frame);
                }
            }
        }
        //draw coord oxes
        if (objects.size() >= 1){
            float d = 0.5f;
            QRgb colorX = qRgb(255, 0, 0);
            QRgb colorY = qRgb(0, 255, 0);
            QRgb colorZ = qRgb(0, 0, 255);
            QVector4D p0 = QVector4D(0.0f, 0.0f, 0.0f, 1.0f);
            QVector4D px = QVector4D(d, 0.0f, 0.0f, 1.0f);
            QVector4D py = QVector4D(0.0f, d, 0.0f, 1.0f);
            QVector4D pz = QVector4D(0.0f, 0.0f, d, 1.0f);
            p0 = p0*globalRotate*MvMp;
            px = px*globalRotate*MvMp;
            py = py*globalRotate*MvMp;
            pz = pz*globalRotate*MvMp;
            QVector3D pScr0  = QVector3D(p0.x()/p0.w(), p0.y()/p0.w(), p0.z()/p0.w());
            QVector3D pScrX  = QVector3D(px.x()/p0.w(), px.y()/p0.w(), px.z()/px.w());
            QVector3D pScrY  = QVector3D(py.x()/p0.w(), py.y()/p0.w(), py.z()/py.w());
            QVector3D pScrZ  = QVector3D(pz.x()/p0.w(), pz.y()/p0.w(), pz.z()/pz.w());
            if (zClipping(pScr0, pScrX)){
                Graphics2D::drawLine(pixFromCoord(pScr0), pixFromCoord(pScrX), colorX, *frame);
            }
            if (zClipping(pScr0, pScrY)){
                Graphics2D::drawLine(pixFromCoord(pScr0), pixFromCoord(pScrY), colorY, *frame);
            }
            if (zClipping(pScr0, pScrZ)){
                Graphics2D::drawLine(pixFromCoord(pScr0), pixFromCoord(pScrZ), colorZ, *frame);
            }
        }
    }
    return frame;
}

void GraphicEngine::setCamera(Camera &camera)
{
    this->camera = camera;
}

void GraphicEngine::addObject(Object &object)
{
    objects.push_back(object);
}

void GraphicEngine::clear()
{
    objects.clear();
}

bool GraphicEngine::zClipping(QVector3D &p1, QVector3D &p2)
{
    const float farPlane = camera.farPlane;
    const float nearPlane = camera.nearPlane;
    if ((p1.z() > farPlane && p2.z() > farPlane) || (p1.z() < nearPlane && p2.z() < nearPlane)){
        return false;
    } else {
        float x = 0.0f;
        float y = 0.0f;
        if (p1.z() < nearPlane){
            x = (p2.x() - p1.x())*(nearPlane - p1.z())/(p2.z() - p1.z()) + p1.x();
            y = (p2.y() - p1.y())*(nearPlane - p1.z())/(p2.z() - p1.z()) + p1.y();
            p1.setX(x);
            p1.setY(y);
            p1.setZ(nearPlane);
        } else if(p1.z() > farPlane){
            x = (p2.x() - p1.x())*(farPlane - p1.z())/(p2.z() - p1.z()) + p1.x();
            y = (p2.y() - p1.y())*(farPlane - p1.z())/(p2.z() - p1.z()) + p1.y();
            p1.setX(x);
            p1.setY(y);
            p1.setZ(farPlane);
        }
        if (p2.z() < nearPlane){
            x = (p2.x() - p1.x())*(nearPlane - p1.z())/(p2.z() - p1.z()) + p1.x();
            y = (p2.y() - p1.y())*(nearPlane - p1.z())/(p2.z() - p1.z()) + p1.y();
            p2.setX(x);
            p2.setY(y);
            p2.setZ(nearPlane);
        } else if(p2.z() > farPlane){
            x = (p2.x() - p1.x())*(farPlane - p1.z())/(p2.z() - p1.z()) + p1.x();
            y = (p2.y() - p1.y())*(farPlane - p1.z())/(p2.z() - p1.z()) + p1.y();
            p2.setX(x);
            p2.setY(y);
            p2.setZ(farPlane);
        }
        return true;
    }
}

QPoint GraphicEngine::pixFromCoord(const QVector3D &coord)
{
    int x = width/2 + coord.x() * width / camera.width;
    int y = height/2 - coord.y() * height / camera.height;
    return QPoint(x, y);
}

void GraphicEngine::rotate(int dyPix, int dxPix)
{
    float dxVal = -1*dxPix*camera.width/width;
    float dyVal = -1*dyPix*camera.height/height;
    float angleX = dxVal*M_PI/camera.width;
    float angleY = dyVal*M_PI/camera.height;
//    for(Object& obj: objects){

        objects[currentObject].rotate(angleX, angleY, 0);
//    }
}

void GraphicEngine::scale(int y)
{
    const float coef = 1.2f/120;
    float scale = 1.0f;
    if(y > 0){
         scale = coef*qAbs(y);
    } else if (y < 0){
        scale = 1.0f / (coef*qAbs(y));
    } else {
        return;
    }
    for(Object& obj: objects){
        obj.scale(scale);
    }
}

void GraphicEngine::zoom(int y)
{
    const float coef = 1.2f/120;
    if(y > 0){
        camera.nearPlane *= coef*qAbs(y);
    } else if (y < 0){
        camera.nearPlane /= coef*qAbs(y);
    }
    camera.update();
}

void GraphicEngine::changeMode()
{
    if (mode == WORLD){
        mode = SPLINE;
    } else if (mode == SPLINE){
        mode = WORLD;
    }
}

bool GraphicEngine::isSplineMode()
{
    return mode == SPLINE;
}

Settings GraphicEngine::getSettings() const
{
    return settings;
}

void GraphicEngine::setSettings(const Settings &value)
{
    settings = value;
    for(Object& obj: objects){
        WireModel wireModel = WireModel(obj.getBSpline(), settings);
        obj.setWireModel(wireModel);
    }
}

void GraphicEngine::rotateScene(int dyPix, int dxPix)
{
    float dxVal = -1*dxPix*camera.width/width;
    float dyVal = -1*dyPix*camera.height/height;
    float angleX = dxVal*M_PI/camera.width;
    float angleY = dyVal*M_PI/camera.height;
    QMatrix4x4 rotationX = QMatrix4x4(1, 0, 0, 0,
                                      0, qCos(angleX), qSin(angleX), 0,
                                      0, -1*qSin(angleX), qCos(angleX), 0,
                                      0, 0, 0, 1);
    QMatrix4x4 rotationY = QMatrix4x4(qCos(angleY), 0, -1*qSin(angleY), 0,
                                      0, 1, 0, 0,
                                      qSin(angleY), 0, qCos(angleY), 0,
                                      0, 0, 0, 1);
    QMatrix4x4 rotation = rotationY * rotationX;
    globalRotate *= rotation;
}

void GraphicEngine::reset()
{
    globalRotate = defaultRotate;
    for(auto& obj: objects){
        obj.reset();
    }
}

void GraphicEngine::setDefaultFontColor(const QRgb &value)
{
    defaultFontColor = value;
}

void GraphicEngine::setGlobalRotate(const QMatrix4x4 &value)
{
    defaultRotate = value;
    globalRotate = value;
}

void GraphicEngine::nextFigure()
{
    if (currentObject < objects.size() - 1){
        currentObject++;
    }
}

void GraphicEngine::prevFigure()
{
    if (currentObject > 0){
        currentObject--;
    }
}
