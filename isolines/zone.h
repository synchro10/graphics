#ifndef ZONE_H
#define ZONE_H

#include <QtWidgets>
#include <QImage>
#include <QSharedPointer>
#include <QRgb>
#include <utility>
#include "legend.h"
#include "options.h"

typedef std::pair<double, double> Coordinate;

class ParametrsIsoline;

class Zone : public QWidget
{    
    friend class ParametrsIsoline;
    Q_OBJECT
public:
    explicit Zone(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) override;
    void defaultParams();
    const Options getOptions();

    void setInterpolation();
    void setGrid();
    void setIsoline();
    void setPoint();
    void setFunction(double (*func_)(double x, double y));
    void setColors(const QVector<QRgb> &value);
    void setIsolineColor(QRgb color);
    void setK(int value);
    void setM(int value);
    void setN(int value);
    void updateValues();
    void setLegend(Legend *value);
    void setOptions(const Options options);

    void addIsoline(double value);
    void clearIsolines();
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;
signals:
    void statusMessage(const QString& message);
public slots:
private:
    int width = 500;
    int height = 500;
    QSharedPointer<QImage> image;
    Legend* legend = nullptr;

    QString getStatus(QMouseEvent *e);
    void fillImage();
    void drawGrid();
    void drawAllIsolines();
    void drawIsoline(const ParametrsIsoline &params, const double value); 
    void initLegend();
    QPoint pixelFromCoord(std::pair<double, double> &coord);
    std::pair<double, double> coordFromPixel(int i, int j);

    int k = 0;
    int m = 0;
    int n = 0;

    double a = 0.0;
    double b = 0.0;
    double c = 1.0;
    double d = 1.0;
    bool isInterpolate = false;
    bool isGrid = false;
    bool isIsoline = false;
    bool isPoint = false;
    double minValue = 0.0;
    double maxValue = 0.0;
    double step = 0.0;
    QVector<double> values;
    QVector<double> customIsolines;
    QVector<QRgb> colors;
    QRgb lineColor = qRgb(0,0,0);

    bool isMapDrawn = false;
    bool isGridDrawn = false;
    bool isIsolineDrawn = false;
    bool isLastIsolineDrawn = false;
    void reset();

    double (*function)(double x, double y) = nullptr;
    void drawLineY(QPoint point1, QPoint point2);
    void drawLineX(QPoint point1, QPoint point2);
    void drawLine(QPoint point1, QPoint point2);
    void drawLinePoint(QPoint point1, QPoint point2);
    void drawPoint3(QPoint point);
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
