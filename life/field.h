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

    uint getCellSize() const;
    void setCellSize(const uint &value);

    uint getGridHeight() const;
    void setGridHeight(const uint &value);

    uint getGridWidth() const;
    void setGridWidth(const uint &value);

    void drawHexagon(uint x, uint y);
    void drawGrid();
    void fillCell(uint x, uint y, QRgb color);

signals:

public slots:

private:
    void clippingLine(QPoint* point1, QPoint* point2);
    void drawLineX(QPoint point1, QPoint point2);
    void drawLineY(QPoint point1, QPoint point2);
    std::pair<QPoint, QPoint> findSpan(QPoint, QRgb color);

    QRgb lineColor;
    QRgb cellColor;
    QRgb fontColor;
    QImage* image = nullptr;
    static const int DEFAULT_WIDTH = 800;
    static const int DEFAULT_HEIGHT = 600;
    uint gridWidth = 5;
    uint gridHeight = 5;
    uint cellSize = 50;
};

#endif // FIELD_H
