#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSharedPointer>
#include "drawingarea.h"

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
    ~View();
private:
    DrawingArea* area = nullptr;
    const int DEFAULT_HEIGHT = 350 + 200;
    const int DEFAULT_WIDTH = 3 * 350 + 100;
};

#endif // VIEW_H
