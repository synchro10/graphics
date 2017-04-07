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
#include "gammawidget.h"
#include "gammafilter.h"
#include "embossfilter.h"
#include "edgewidget.h"
#include "edgerobertfilter.h"
#include "edgesobelfilter.h"
#include "ditheringfilter.h"
#include "ditheringwidget.h"
#include "dithringfloydfilter.h"
#include "zonea.h"

class Executor : public QObject
{
    Q_OBJECT
public:
    explicit Executor(QObject *parent = 0);
    void execute();

    void setZoneA(ZoneA *value);

signals:

public slots:
    void blackWhiteFilter();
    void negativeFilter();
    void ditheringFilter     ();
    void ditheringFloydFilter();
    void ditheringFloydButton();
    void upscaleFilter       ();
    void rotateButton        ();
    void rotateFilter        (int);
    void rotateFilter1       ();
    void gammaButton         ();
    void gammaFilter         (int);
    void gammaFilter1        ();
    void edgeRobertButton    ();
    void edgeRobertFilter    (int);
    void edgeRobertFilter1   ();
    void edgeSobelButton     ();
    void edgeSobelFilter     (int);
    void edgeSobelFilter1    ();
    void embossFilter        ();
    void waterFilter         ();
    void blurFilter          ();
    void sharpenFilter       ();
    void runLastFilter       ();
private:
    QSharedPointer<View> view;
    QThreadPool* threadPool;
    QWidget* controlWidget = nullptr;
    void (Executor::*lastFilter)() = nullptr;
    ZoneA *zoneA = nullptr;

    void setCImage(QImage* image);
    void setup();
    void addTask(Filter* filter);
};

#endif // EXECUTOR_H
