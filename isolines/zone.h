#ifndef ZONE_H
#define ZONE_H

#include <QtWidgets>
#include <QImage>
#include <QSharedPointer>
#include <QRgb>
#include <utility>
#include "legend.h"

class ParametrsIsoline;

class Zone : public QWidget
{    
    friend class ParametrsIsoline;
    Q_OBJECT
public:
    explicit Zone(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) override;
    void defaultParams();
    void setInterpolation();
    void setFunction(double (*func_)(double x, double y));
    void setColors(const QVector<QRgb> &value);

    void setK(int value);

    void setM(int value);

    void setN(int value);

    void setLegend(Legend *value);

signals:

public slots:
private:
    int width = 500;
    int height = 500;
    QSharedPointer<QImage> image;
    Legend* legend = nullptr;

    void fillImage();
    void drawGrid();
    void drawAllIsolines();
    void drawIsoline(const ParametrsIsoline &params, const double value);
    void updateValues();
    void initLegend();
    QPoint pixelFromCoord(double x, double y);
    std::pair<double, double> coordFromPixel(int i, int j);

    int k = 0;
    int m = 0;
    int n = 0;

    double a = 0.0;
    double b = 0.0;
    double c = 1.0;
    double d = 1.0;
    bool isInterpolate = false;
    double minValue = 0.0;
    double maxValue = 0.0;
    double step = 0.0;
    QVector<double> values;
    QVector<QRgb> colors;
    QRgb lineColor = qRgb(0,0,0);

    double (*function)(double x, double y) = nullptr;
    void drawLineY(QPoint point1, QPoint point2);
    void drawLineX(QPoint point1, QPoint point2);
    void drawLine(QPoint point1, QPoint point2);


};

class ParametrsIsoline{
public:
    ParametrsIsoline(Zone *zone, int i, int j);

    double f1 = 0.0;
    double f2 = 0.0;
    double f3 = 0.0;
    double f4 = 0.0;
    double xi = 0.0;
    double yj = 0.0;
    double xi1 = 0.0;
    double yj1 = 0.0;
    double dx = 0.0;
    double dy = 0.0;
};

#endif // ZONE_H
