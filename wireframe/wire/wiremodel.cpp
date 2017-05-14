#include "wiremodel.h"

WireModel::WireModel()
{

}

void WireModel::addEdge(QVector3D& p1, QVector3D& p2)
{
    model.push_back(Edge(p1, p2));
}

QVector<WireModel::Edge> WireModel::getModel() const
{
    return model;
}
