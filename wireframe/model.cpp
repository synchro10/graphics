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
    WireModel wireModel = WireModel();
    QVector3D p1 = QVector3D(0,0,0);
    QVector3D p2 = QVector3D(1,1,1);
    wireModel.addEdge(p1, p2);
    simple.setWireModel(wireModel);

    engine.addObject(simple);
    engine.setCamera(camera);
}

void Model::openFileHandle(const QString &fileName)
{
    std::cout << "Model : Open" << std::endl;
}

void Model::mouseMoveHandle(QMouseEvent e)
{
    QImage* image = engine.render();
    std::cout << e.pos().x() << " " << e.pos().y() << std::endl;
    emit sendFrame(QSharedPointer<QImage>(image));
}

void Model::wheelMoveHandle(QWheelEvent e)
{
    std::cout << e.angleDelta().y() << std::endl;
    int i = (int)rand()%400;
    emit sendFrame(QSharedPointer<QImage>(new QImage(i, i, QImage::Format_RGB32)));
}
