#include "graphicengine.h"
#include "graphics2d.h"

GraphicEngine::GraphicEngine()
{
    //frame = new QImage(width, height, QImage::Format_RGB32);
}

QImage *GraphicEngine::render()
{
    frame = new QImage(width, height, QImage::Format_RGB32);
    clearFrame();
    const QMatrix4x4& Mv = camera.getViewTransform();
    const QMatrix4x4& Mp = camera.getProjectionTransform();
    const QMatrix4x4& MvMp = Mv*Mp;
//    const QMatrix4x4& MvMp = Mv;
    for(const Object& object: objects){
        const auto& edges = object.getWireModel().getModel();
        const QMatrix4x4& Mw = object.worldTransform;
        for(WireModel::Edge edge: edges){
            const QVector4D& position1 = QVector4D(edge.first.x(), edge.first.y(), edge.first.z(), 1.0);
            const QVector4D& position2 = QVector4D(edge.second.x(), edge.second.y(), edge.second.z(), 1.0);
            QVector4D p1 = position1*Mw*MvMp;
            QVector4D p2 = position2*Mw*MvMp;
            float w = p1.w();
            QVector3D positionScr1 = QVector3D(p1.x()/w, p1.x()/w, p1.x()/w);
            w = p2.w();
            QVector3D positionScr2 = QVector3D(p2.x()/w, p2.x()/w, p2.x()/w);
            if (zClipping(positionScr1, positionScr2)){
                QPoint p1 = positionScr1.toPoint();
                QPoint p2 = positionScr2.toPoint();
                Graphics2D::drawLine(p1, p2, defaultLineColor, *frame);
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

//todo test
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

void GraphicEngine::clearFrame()
{
    QRgb* pixels = reinterpret_cast<QRgb*>(frame->bits());
    int pixPerLine = frame->bytesPerLine() / sizeof(QRgb);
    int height = frame->height();
    int width = frame->width();
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            pixels[i * pixPerLine + j] = defaultFontColor;
        }
    }
}
