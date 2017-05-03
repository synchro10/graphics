#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QtWidgets>
#include <QImage>
#include <iostream>

class DrawingArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) override;
    void setBufferImage(const QSharedPointer<QImage> &value);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    void mouseMoveEvent(QMouseEvent *e) override;
    void wheelEvent(QWheelEvent *event) override;
signals:
    void mouseMove(QMouseEvent e);
    void wheelMove(QWheelEvent e);
public slots:
    void getFrame(const QSharedPointer<QImage> &value);
private:
    int width = 800;
    int height = 600;
    QSharedPointer<QImage> image;
    QSharedPointer<QImage> bufferImage;
};

#endif // DRAWINGAREA_H
