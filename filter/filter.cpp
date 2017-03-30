#include "filter.h"
#include <QDebug>
#include <iostream>
#include <assert.h>

Filter::Filter(QObject *parent) : QObject(parent)
{
    image = QSharedPointer<QImage>();
}

void Filter::run()
{
    processImage();
    emit finished(new QImage(*image.data()));
}

void Filter::setImage(QImage *image_)
{
    assert(image_ != nullptr);
    image = QSharedPointer<QImage>(image_);
    height = image->height();
    width = image->width();
    //tmp
    if (height != 352 && width != 352){
        qDebug() << "in filter height width " << height << " " << width;
    }
}
