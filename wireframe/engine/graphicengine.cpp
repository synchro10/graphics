#include "graphicengine.h"

GraphicEngine::GraphicEngine()
{
    frame = QImage(width, height, QImage::Format_RGB32);
}

QImage &GraphicEngine::render()
{
    const QMatrix4x4& Mv = camera.getViewTransform();
    const QMatrix4x4& Mp = camera.getProjectionTransform();
    const QMatrix4x4& MvMp = Mv*Mp;
    for(const Object& object: objects){
        const auto& edges = object.getWireModel().getModel();
        const QMatrix4x4& Mw = object.worldTransform;
        for(WireModel::Edge edge: edges){
            const QVector4D& position1 = QVector4D(edge.first);
            const QVector4D& position2 = QVector4D(edge.second);
            QVector4D p1 = position1*Mw*MvMp;
            QVector4D p2 = position2*Mw*MvMp;
            float w = p1.w();
            QVector3D positionScr1 = QVector3D(p1.x()/w, p1.x()/w, p1.x()/w);
            w = p2.w();
            QVector3D positionScr2 = QVector3D(p2.x()/w, p2.x()/w, p2.x()/w);
            if (zClipping(positionScr1, positionScr2)){

            }
        }
    }

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
