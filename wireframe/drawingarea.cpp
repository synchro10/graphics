#include "drawingarea.h"

DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
    setFixedSize(width, height);
    image = QSharedPointer<QImage>(new QImage(width, height, QImage::Format_RGB32));
}

void DrawingArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect dirtyRect = event->rect();
    painter.drawImage(dirtyRect, *image.data(), dirtyRect);
}

void DrawingArea::setBufferImage(const QSharedPointer<QImage> &value)
{
    bufferImage = value;
}

void DrawingArea::getFrame(const QSharedPointer<QImage> &value)
{
    setBufferImage(value);
    image.swap(bufferImage);
    update();
}

int DrawingArea::getHeight() const
{
    return height;
}

void DrawingArea::setHeight(int value)
{
    height = value;
}

void DrawingArea::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() == Qt::RightButton){
        emit(mouseMove(*e));
    }
}

void DrawingArea::wheelEvent(QWheelEvent *event)
{
    emit(wheelMove(*event));
}

int DrawingArea::getWidth() const
{
    return width;
}

void DrawingArea::setWidth(int value)
{
    width = value;
}
