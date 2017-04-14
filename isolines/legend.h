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

    void setColors(const QVector<QRgb>& value);

    void setValues(const QVector<double>& value);

    void init(int n, const QVector<QRgb>& colors, const QVector<double>& values);

signals:

public slots:
private:
    int width = 500;
    int height = 50;
    QSharedPointer<QImage> image;

    QRgb getInterpolateColor(int i);

    int n = 0;
    bool isInterpolate = false;
    QVector<QRgb> colors = QVector<QRgb>();
    QVector<double> values = QVector<double>();
};

#endif // LEGEND_H
