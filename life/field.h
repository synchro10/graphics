#ifndef FIELD_H
#define FIELD_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <vector>

class Field : public QWidget
{
    Q_OBJECT
public:
    explicit Field(QWidget *parent = 0);

    ~Field();
    void paintEvent(QPaintEvent *event) override;
    void drawLine(QPoint point1, QPoint point2);

    void changeParam(uint width, uint height, uint cell);
    uint getCellSize() const;
    void setCellSize(const uint &value);

    uint getGridHeight() const;
    void setGridHeight(const uint &value);

    uint getGridWidth() const;
    void setGridWidth(const uint &value);

    void drawHexagon(uint x, uint y);
    void drawGrid();
    void fillCell(uint x, uint y, QRgb color);
    void setField(std::vector<std::vector<bool> >*);

    void mousePressEvent(QMouseEvent *e) override;

    bool isXOR = false;

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
    static const int DEFAULT_WIDTH = 1300;
    static const int DEFAULT_HEIGHT = 700;

    std::vector<std::vector<bool> >* field;
    uint gridWidth = 5;
    uint gridHeight = 5;
    uint cellSize = 100;
};

#endif // FIELD_H
