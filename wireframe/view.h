#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QtWidgets>
#include "optionsdialog.h"
#include "drawingarea.h"

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
    ~View();
    DrawingArea *getArea() const;

    OptionsDialog *getOptionsDiagog() const;

signals:
    void openFile(const QString& fileName);
    void changeState();
    void reset();

public slots:
    void open();
    void spline();
    void init();
    void showOptions();
    void about();
private:
    int DEFAULT_HEIGHT = 600;
    int DEFAULT_WIDTH = 800;
    void createActions();
    void createMenus();
    void createToolbar();
    void configureDialogs();

    QMenu *fileMenu;
    QMenu *helpMenu;
    QToolBar *toolbar;

    QAction *openAct;
    QAction *splineAct;
    QAction *initAct;
//    QAction *saveAct;
    QAction *optionAct;
    QAction *exitAct;
    QAction *aboutAct;


    OptionsDialog *optionsDiagog = nullptr;
    DrawingArea* area = nullptr;
};

#endif // VIEW_H
