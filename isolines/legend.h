#ifndef LEGEND_H
#define LEGEND_H

#include <QtWidgets>
#include <QImage>
#include <QVector>

class Legend : public QWidget
{
    Q_OBJECT
public:
    explicit Legend(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) override;

    void setN(int value);

    void setInterpolation();

    void setColors(QVector<QRgb> *value);

    void setValues(QVector<double> *value);

signals:

public slots:
private:
    int width = 500;
    int height = 50;
    QSharedPointer<QImage> image;

    QRgb getInterpolateColor(int i);

    int n = 0;
    bool isInterpolate = false;
    QVector<QRgb>* colors;
    QVector<double>* values;
};

#endif // LEGEND_H
