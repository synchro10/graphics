#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QtWidgets>
//#include "zone.h"
#include "zonea.h"
#include "controlpanel.h"

class DrawingArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) override;
    void open(const QString &fileName);
    void select();
signals:

public slots:
private:
    Zone* zoneA = nullptr;
    Zone* zoneB = nullptr;
    Zone* zoneC = nullptr;
    ControlPanel* controlPanel = nullptr;

    QHBoxLayout* zoneLayout = nullptr;
    QVBoxLayout *mainLayout = nullptr;
};

#endif // DRAWINGAREA_H
