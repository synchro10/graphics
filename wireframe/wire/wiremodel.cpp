#include "wiremodel.h"

WireModel::WireModel()
{

}

void WireModel::addEdge(WireModel::Edge &edge)
{
    model.push_back(edge);
}

QVector<WireModel::Edge> WireModel::getModel() const
{
    return model;
}
