#ifndef ZONEA_H
#define ZONEA_H

#include "zone.h"

class ZoneA : public Zone
{
public:
    ZoneA(QWidget *parent);

    void paintEvent(QPaintEvent *event) override;
    void setImage(QImage* image_);

    void mouseMoveEvent(QMouseEvent *e) override;//todo
    void setSelect(){ isSelect = !isSelect; }

private:
    QSharedPointer<QImage> image;
    QSharedPointer<QImage> imagePrototype;
    QImage* correctImage(QImage* image_);
    void updateSelector();
    int height = 0;
    int width = 0;

    int selectorSize = 0;
    int selectorPosX = 0;
    int selectorPosY = 0;
    void paintSelector(QImage *image_);
    bool isSelect = false;
};

#endif // ZONEA_H
