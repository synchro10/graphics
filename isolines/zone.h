#ifndef ZONE_H
#define ZONE_H

#include <QtWidgets>
#include <QImage>
#include <QSharedPointer>
#include <QRgb>
#include "legend.h"

class Zone : public QWidget
{
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
    void drawIsoline();
    void updateValues();
    void initLegend();

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
};

#endif // ZONE_H
