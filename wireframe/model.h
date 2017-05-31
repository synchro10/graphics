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
    void initEngine();
public slots:
    void openFileHandle(const QString& fileName);
    void mouseMoveHandle(QMouseEvent e);
    void wheelMoveHandle(QWheelEvent e);
    void mousePressHandle(QMouseEvent e);
    void changeStateHandle();
signals:
    void sendFrame(const QSharedPointer<QImage> &value);
private:
    GraphicEngine engine;
    QPoint startPos;
};

#endif // MODEL_H
