#include "model.h"

Model::Model(QObject *parent)
{
    initEngine();
}

void Model::initEngine()
{
    Camera camera;
    camera.defaultSettings();
    Object simple = Object();
    simple.defaultSettings();

    BSpline bspline;
    bspline.addPoint(-1,0);
    bspline.addPoint(-1,0);
    bspline.addPoint(-1,0);
    bspline.addPoint(0,1);
    bspline.addPoint(1,1);
    bspline.addPoint(2,0);
    bspline.addPoint(2,0);
    bspline.addPoint(2,0);
    bspline.createValues();
    simple.setBSpline(bspline);

    WireModel wireModel = WireModel(bspline, Settings());

    simple.setWireModel(wireModel);
    simple.move(-1,-1,-1);

    engine.addObject(simple);
    engine.setCamera(camera);
}

void Model::openFileHandle(const QString &fileName)
{
    engine.clear();
    if (Parser::initEngine(fileName, engine)){
        emit sendSettings(engine.getSettings());
        std::cout << "sucsess init from file" << std::endl;
    } else {
        std::cout << "fail init from file" << std::endl;
    }
    QImage* image = engine.render();
    emit sendFrame(QSharedPointer<QImage>(image));
}

void Model::mouseMoveHandle(QMouseEvent e)
{
    if (engine.isSplineMode()){
        return;
    }
    if (e.buttons() == Qt::RightButton){
        engine.rotate(e.pos().x() - startPos.x(), e.pos().y() - startPos.y());
    } else if (e.buttons() == Qt::LeftButton){
        engine.rotateScene(e.pos().x() - startPos.x(), e.pos().y() - startPos.y());
    }
    QImage* image = engine.render();
    startPos = e.pos();
    emit sendFrame(QSharedPointer<QImage>(image));
}

void Model::wheelMoveHandle(QWheelEvent e)
{
    if (engine.isSplineMode()){
        return;
    }
    engine.zoom(e.angleDelta().y());
    QImage* image = engine.render();
    emit sendFrame(QSharedPointer<QImage>(image));
}

void Model::mousePressHandle(QMouseEvent e)
{

    if (engine.isSplineMode()){
        return;
    }
    startPos = e.pos();
}

void Model::changeStateHandle()
{
    engine.changeMode();
    QImage* image = engine.render();
    emit sendFrame(QSharedPointer<QImage>(image));
}

void Model::setSettingsHandle(Settings settings)
{
    int n = settings.n;
    int m = settings.m;
    int k = settings.k;
    float a = settings.a;
    float b = settings.b;
    float c = settings.c;
    float d = settings.d;
    if (1 <= n && 1 <= m && 1 <= k && 0.0 <= a && a < b && b <= 1.0 && 0.0 <= c && c < d && d <= 6.31){
        engine.setSettings(settings);
        QImage* image = engine.render();
        emit sendFrame(QSharedPointer<QImage>(image));
    } else {
        emit sendSettings(engine.getSettings());
    }
}

void Model::initHandle()
{
    engine.reset();
    QImage* image = engine.render();
    emit sendFrame(QSharedPointer<QImage>(image));
}

void Model::nextHandle()
{
    engine.nextFigure();
    QImage* image = engine.render();
    emit sendFrame(QSharedPointer<QImage>(image));
}

void Model::prevHandle()
{
    engine.prevFigure();
    QImage* image = engine.render();
    emit sendFrame(QSharedPointer<QImage>(image));
}
