#ifndef ZONEB_H
#define ZONEB_H

#include "zone.h"
#include <QImage>

class ZoneB : public Zone
{
public:
    ZoneB(QWidget *parent);

    void paintEvent(QPaintEvent *event) override;
    void setImage(QImage* image_);
    QImage* getImage();
private:
    QSharedPointer<QImage> image;
};

#endif // ZONEB_H
