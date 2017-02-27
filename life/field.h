#ifndef FIELD_H
#define FIELD_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>

class Field : public QWidget
{
    Q_OBJECT
public:
    explicit Field(QWidget *parent = 0);
    ~Field();
    void paintEvent(QPaintEvent *event) override;
    void drawLine(QPoint point1, QPoint point2);

signals:

public slots:

private:
    void clippingLine(QPoint* point1, QPoint* point2);
    void drawLineX(QPoint point1, QPoint point2);
    void drawLineY(QPoint point1, QPoint point2);

    QRgb lineColor;
    QRgb cellColor;
    QRgb fontColor;
    QImage* image = nullptr;
    static const int DEFAULT_WIDTH = 800;
    static const int DEFAULT_HEIGHT = 600;
};

#endif // FIELD_H
