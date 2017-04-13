#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QtWidgets>
#include "drawingarea.h"
#include "options.h"

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
    ~View(){}

private slots:
    void open();
    void interpolation();
    void grid();
    void isoline();
    void point();
    void clear();
    void showOptions();
    void setOptions(const Options options);
    void about();

private:
    void createActions();
    void createMenus();
    void createToolbar();
    void configureDialogs();

    QMenu *fileMenu;
    QMenu *helpMenu;
    QToolBar *toolbar;

    QAction *openAct;
    QAction *interpolateAct;
    QAction *gridAct;
    QAction *isolineAct;
    QAction *pointAct;
    QAction *clearAct;
    QAction *optionAct;
    QAction *exitAct;

    OptionsDialog *optionsDiagog;
    QAction *aboutAct;
    DrawingArea* area = nullptr;
};

#endif // VIEW_H
