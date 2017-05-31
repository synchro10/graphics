#include "model.h"

Model::Model(QObject *parent)
{
    initEngine();
}

void Model::initEngine()
{
    Camera camera;
    camera.defaultSettings();
    Object simple = Object();
    simple.defaultSettings();

    BSpline bspline;
    bspline.addPoint(-1,0);
    bspline.addPoint(-1,0);
    bspline.addPoint(-1,0);
    bspline.addPoint(0,1);
    bspline.addPoint(1,1);
    bspline.addPoint(2,0);
    bspline.addPoint(2,0);
    bspline.addPoint(2,0);
    bspline.createValues();
    simple.setBSpline(bspline);

    WireModel wireModel = WireModel(bspline);
//    QVector3D p1 = QVector3D(-1,-1,-1);
//    QVector3D p2 = QVector3D(-1,-1,1);
//    QVector3D p3 = QVector3D(-1,1,-1);
//    QVector3D p4 = QVector3D(-1,1,1);
//    QVector3D p5 = QVector3D(1,-1,-1);
//    QVector3D p6 = QVector3D(1,-1,1);
//    QVector3D p7 = QVector3D(1,1,-1);
//    QVector3D p8 = QVector3D(1,1,1);
//    wireModel.addEdge(p1, p2);
//    wireModel.addEdge(p2, p4);
//    wireModel.addEdge(p4, p3);
//    wireModel.addEdge(p3, p1);

//    wireModel.addEdge(p5, p6);
//    wireModel.addEdge(p6, p8);
//    wireModel.addEdge(p8, p7);
//    wireModel.addEdge(p7, p5);

//    wireModel.addEdge(p1, p5);
//    wireModel.addEdge(p3, p7);
//    wireModel.addEdge(p4, p8);
//    wireModel.addEdge(p2, p6);
    simple.setWireModel(wireModel);

    QVector<QPointF> p = bspline.getPoints(10, 0.0f, 1.0f);
    engine.addObject(simple);
    engine.setCamera(camera);
}

void Model::openFileHandle(const QString &fileName)
{
    std::cout << "Model : Open" << std::endl;
}

void Model::mouseMoveHandle(QMouseEvent e)
{
    if (engine.isSplineMode()){
        return;
    }
    engine.rotate(e.pos().x() - startPos.x(), e.pos().y() - startPos.y());
    QImage* image = engine.render();
    startPos = e.pos();
    emit sendFrame(QSharedPointer<QImage>(image));
}

void Model::wheelMoveHandle(QWheelEvent e)
{
    if (engine.isSplineMode()){
        return;
    }
    engine.scale(e.angleDelta().y());
    QImage* image = engine.render();
    emit sendFrame(QSharedPointer<QImage>(image));
}

void Model::mousePressHandle(QMouseEvent e)
{
    if (engine.isSplineMode()){
        return;
    }
    startPos = e.pos();
}

void Model::changeStateHandle()
{
    engine.changeMode();
    QImage* image = engine.render();
    emit sendFrame(QSharedPointer<QImage>(image));
}
