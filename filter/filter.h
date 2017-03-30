#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include <QRunnable>
#include <QSharedPointer>
#include <QImage>

class Filter : public QObject, public QRunnable
{
    Q_OBJECT
public:
    explicit Filter(QObject *parent = 0);
    void run();
    virtual void processImage(){}
    void setImage(QImage* image_);

signals:
    void finished(QImage* image_);
public slots:
protected:
    QSharedPointer<QImage> image;
    int height = 0;
    int width = 0;
};

#endif // FILTER_H
