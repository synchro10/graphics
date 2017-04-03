#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QWidget>
#include <QVector>
#include "zone.h"

class DrawingArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) override;
    void open(const QString &fileName);
    void setInterpolation();
signals:

public slots:
private:
    Zone* zone = nullptr;
    QWidget* legend = nullptr;
    QVBoxLayout *mainLayout = nullptr;
};

#endif // DRAWINGAREA_H
