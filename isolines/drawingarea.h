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
signals:

public slots:
private:
    QWidget* zone = nullptr;
    QWidget* legend = nullptr;
    QVBoxLayout *mainLayout = nullptr;
};

#endif // DRAWINGAREA_H
