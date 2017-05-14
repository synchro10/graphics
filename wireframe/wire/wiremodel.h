#ifndef WIREMODEL_H
#define WIREMODEL_H

#include <iostream>
#include <QVector>
#include <QVector3D>

class WireModel
{
public:
    typedef std::pair<QVector3D, QVector3D> Edge;
    WireModel();
    void addEdge(QVector3D &p1, QVector3D &p2);
    QVector<Edge> getModel() const;

private:
    QVector<Edge> model;
};

#endif // WIREMODEL_H
