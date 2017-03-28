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
    virtual void setImage(QImage* image_) = 0;
    virtual void setSelect(){ }
    int getSize() const;
    void drawDottedRect(QImage* image, int x0, int y0, int x1, int y1);
    void drawDottedLine(QImage* image, QPoint& start, QPoint& end);
    const int size = 352;
    const QRgb lineColor = qRgb(0,0,0);
    const QRgb fontColor = qRgb(255,255,255);
    const QRgb testColor = qRgb(255,0,0);
signals:

public slots:

private:
    void drawDottedLineY(QImage* image, QPoint& start, QPoint& end);
    void drawDottedLineX(QImage* image, QPoint& start, QPoint& end);
};

#endif // ZONE_H
