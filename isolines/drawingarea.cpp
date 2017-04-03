#include "drawingarea.h"

DrawingArea::DrawingArea(QWidget *parent) : QWidget(parent)
{
    zone = new Zone(this);
    mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);
    mainLayout->addWidget(zone);
    setLayout(mainLayout);
}

void DrawingArea::paintEvent(QPaintEvent *event)
{
//    zone->update();
//    legend->update();
}

void DrawingArea::open(const QString &fileName){
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)){
        return;
    }
    QTextStream in(&file);
    int k = 0;
    int m = 0;
    int n = 0;

    QString str = in.readLine();
    QStringList words = str.split(" ");
    if (words.length() < 2){
        file.close();
        QMessageBox::about(this, tr("Fail"),tr("bad format"));
        return;
    }
    k = words.at(0).toInt();
    m = words.at(1).toInt();

    str = in.readLine();
    words = str.split(" ");
    if (words.length() < 1){
        file.close();
        QMessageBox::about(this, tr("Fail"),tr("bad format"));
        return;
    }
    n = words.at(0).toInt();



    file.close();
    return;
}

void DrawingArea::setInterpolation()
{
    zone->setInterpolation();
    zone->update();
}
