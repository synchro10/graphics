#ifndef MODEL_H
#define MODEL_H

#include <iostream>
#include <QObject>
#include <QtWidgets>
#include "engine/graphicengine.h"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = 0);
public slots:
    void openFileHandle(const QString& fileName);
    void mouseMoveHandle(QMouseEvent e);
    void wheelMoveHandle(QWheelEvent e);
signals:
    void sendFrame(const QSharedPointer<QImage> &value);
private:
    GraphicEngine engine;
};

#endif // MODEL_H
