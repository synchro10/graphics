#include "wiremodel.h"

WireModel::WireModel()
{

}

WireModel::WireModel(BSpline &bspline)
{
    BSpline::Settings params = bspline.settings;
    int n = params.n;
    int m = params.m;
    int k = params.k;
    auto values = bspline.getPoints(n*k, params.a, params.b);
    float v[(m+1)*k];
    for(int i = 0; i <= (m+1)*k - 1; i++){
        v[i] = i*2*M_PI/((m+1)*k - 1);
    }
    for(int i = 1; i <= n*k; i++){
        for(int j = 1; j <= (m+1)*k - 1; j++){
            QVector3D Pij = QVector3D(values[i].y()*qCos(v[j]), values[i].y()*qSin(v[j]), values[i].x());
            QVector3D Pi1j = QVector3D(values[i-1].y()*qCos(v[j]), values[i-1].y()*qSin(v[j]), values[i-1].x());
            QVector3D Pij1 = QVector3D(values[i].y()*qCos(v[j-1]), values[i].y()*qSin(v[j-1]), values[i].x());
            if ((i - 1) % k == 0){
                addEdge(Pij, Pij1);
            }
            if ((j - 1) % k == 0){
                addEdge(Pij, Pi1j);
            }
        }
    }
}

void WireModel::addEdge(QVector3D& p1, QVector3D& p2)
{
    model.push_back(Edge(p1, p2));
}

QVector<WireModel::Edge> WireModel::getModel() const
{
    return model;
}
