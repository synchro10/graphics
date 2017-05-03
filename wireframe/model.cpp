#include "model.h"

Model::Model(QObject *parent)
{

}

void Model::openFileHandle(const QString &fileName)
{
    std::cout << "Model : Open" << std::endl;
}

void Model::mouseMoveHandle(QMouseEvent e)
{
    std::cout << e.pos().x() << " " << e.pos().y() << std::endl;
}

void Model::wheelMoveHandle(QWheelEvent e)
{
    std::cout << e.angleDelta().y() << std::endl;
    int i = (int)rand()%400;
    emit sendFrame(QSharedPointer<QImage>(new QImage(i, i, QImage::Format_RGB32)));
}
