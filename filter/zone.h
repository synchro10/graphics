#ifndef ZONE_H
#define ZONE_H

#include <QtWidgets>
#include <QImage>
#include <QColor>
#include <QSharedPointer>
#include <QPoint>

class Zone : public QWidget
{
    Q_OBJECT
public:
    explicit Zone(QWidget *parent = 0);

    void paintEvent(QPaintEvent *event) override;

    int getSize() const;
    void drawDottedRect(int x0, int y0, int x1, int y1);
    void drawDottedLine(QPoint& start, QPoint& end);

signals:

public slots:

private:
    const int size = 352;
    QRgb lineColor = qRgb(0,0,0);
    QRgb fontColor = qRgb(255,255,255);
    QRgb testColor = qRgb(255,0,0);
    QSharedPointer<QImage> image;

    void drawDottedLineY(QPoint& start, QPoint& end);
    void drawDottedLineX(QPoint& start, QPoint& end);
};

#endif // ZONE_H
