#ifndef DRAWINGAREA_H
#define DRAWINGAREA_H

#include <QtWidgets>
#include "zone.h"
#include "zonea.h"
#include "zoneb.h"
#include "controlpanel.h"

class DrawingArea : public QWidget
{
    Q_OBJECT
public:
    explicit DrawingArea(QWidget *parent = 0);
    void paintEvent(QPaintEvent *event) override;
    void open(const QString &fileName);
    void save(const QString &fileName);
    void select();
    void moveToB();
    void setCImage(QImage* image);
    void moveFromC();
    QImage *getImageB();
    void setControlPanel(QWidget *value);

    ZoneA *getZoneA() const;

signals:

public slots:
private:
    ZoneA* zoneA = nullptr;
    ZoneB* zoneB = nullptr;
    ZoneB* zoneC = nullptr;
    QWidget* controlPanel = nullptr;

    QHBoxLayout* zoneLayout = nullptr;
    QVBoxLayout *mainLayout = nullptr;
};

#endif // DRAWINGAREA_H
