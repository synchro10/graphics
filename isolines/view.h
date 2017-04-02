#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QtWidgets>
#include "drawingarea.h"

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
    ~View(){}

private slots:
    void open();
    void about();

private:
    void createActions();
    void createMenus();
    void createToolbar();

    QMenu *fileMenu;
    QMenu *helpMenu;
    QToolBar *toolbar;

    QAction *openAct;
    QAction *exitAct;

    QAction *aboutAct;
    DrawingArea* area = nullptr;
};

#endif // VIEW_H
