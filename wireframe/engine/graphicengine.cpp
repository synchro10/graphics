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

bool GraphicEngine::zClipping(QVector3D &p1, QVector3D &p2)
{
    const float farPlane = camera.farPlane;
    const float nearPlane = camera.nearPlane;
    if (p1.z > farPlane && p2.z > farPlane || p1.z < nearPlane && p2.z < nearPlane){
        return false;
    } else {
        float x = 0.0f;
        float y = 0.0f;
        if (p1.z() < nearPlane){
            //todo
        } else if(p1.z() > farPlane){

        }
        if (p2.z() < nearPlane){

        } else if(p2.z() > farPlane){

        }

    }
}
