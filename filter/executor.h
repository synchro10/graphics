#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <QObject>
#include <QSharedPointer>
#include <QThreadPool>
#include "view.h"
#include "blackwhitefilter.h"
#include "negativefilter.h"
#include "blurfilter.h"
#include "sharpenfilter.h"
#include "waterfilter.h"
#include "upscaledfilter.h"
#include "rotatefilter.h"
#include <iostream>
#include "rotatewidget.h"

class Executor : public QObject
{
    Q_OBJECT
public:
    explicit Executor(QObject *parent = 0);
    void execute();

signals:

public slots:
    void blackWhiteFilter();
    void negativeFilter();
    void ditheringFilter     ();
    void ditheringErrorFilter();
    void upscaleFilter       ();
    void rotateButton        ();
    void rotateFilter        (int);
    void gammaFilter         ();
    void edgeRobertFilter    ();
    void edgeSobelFilter     ();
    void edgeSpecFilter      ();
    void embossFilter        ();
    void waterFilter         ();
    void blurFilter          ();
    void sharpenFilter       ();
private:
    QSharedPointer<View> view;
    QThreadPool* threadPool;

    void setCImage(QImage* image);
    void setup();
    void addTask(Filter* filter);
};

#endif // EXECUTOR_H
