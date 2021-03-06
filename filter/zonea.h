#ifndef ZONEA_H
#define ZONEA_H

#include "zone.h"
#include "zoneb.h"

class ZoneA : public Zone
{
    Q_OBJECT
public:
    ZoneA(QWidget *parent);

    void paintEvent(QPaintEvent *event) override;
    void setImage(QImage* image_);
    QImage* getSelectedImage();
    void mouseMoveEvent(QMouseEvent *e) override;
    void mousePressEvent(QMouseEvent *e) override;
    void setSelect();

    void setZoneB(ZoneB *value);
signals:
    void lastFilter();
private:
    QSharedPointer<QImage> image;
    QSharedPointer<QImage> imagePrototype;
    ZoneB* zoneB = nullptr;
    QImage* scaleImage(QImage* image_);
    void updateSelector();
    int height = 0;
    int width = 0;

    int selectorSize = 0;
    float selectorSizef = 0.0f;
    int selectorPosX = 0;
    int selectorPosY = 0;
    void paintSelector(QImage *image_);
    bool isSelect = false;
};

#endif // ZONEA_H
