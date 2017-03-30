#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSharedPointer>
#include "drawingarea.h"
#include <QImage>

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
    ~View(){}
    void setImageC(QImage* image);
    QImage* getImageB();

    QAction *blackWhiteAct;
    QAction *negativeAct;
    QAction *ditheringAct;
    QAction *ditheringErrorAct;
    QAction *upscaleAct;
    QAction *rotateAct;
    QAction *gammaAct;
    QAction *edgeRobertAct;
    QAction *edgeSobelAct;
    QAction *edgeSpecAct;
    QAction *embossAct;
    QAction *waterAct;
    QAction *blurAct;
    QAction *sharpenAct;
    void setControl(QWidget* controlWidget);

private slots:
    void open();
    void save();
    void about();
    void select();
    void moveFromC();

private:
    void createActions();
    void createMenus();
    void createToolbar();

    QMenu *editMenu;
    QMenu *fileMenu;
    QMenu *filterMenu;
    QMenu *helpMenu;
    QToolBar *toolbar;
    QToolBar *filterToolbar;

    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *selectAct;
    QAction *moveCAct;

    QAction *aboutAct;

    DrawingArea* area = nullptr;
    const int DEFAULT_HEIGHT = 350 + 300;
    const int DEFAULT_WIDTH = 3 * 350 + 100;
};

#endif // VIEW_H
