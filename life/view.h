#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QtWidgets>
#include <memory>
#include "field.h"
#include "model.h"

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
    ~View(){}
    Field *getField() const;

    void setModel(Model *value);

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void open();
    void save();
    void about();
    void startGame(uint width, uint height, int cellSize);
    void nextIteration();
    void run();
    void stop();
    void clearField();
    void replaceMode();
    void xorMode();
    void impact();
    void params();
    void newGame();

private:
    std::unique_ptr<Field> field;
    Model *model;

    QScrollArea *scroll;

    void createActions();
    void createMenus();
    void createToolbar();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;
    QToolBar *toolbar;

    QAction *openAct;
    QAction *saveAct;
    QAction *exitAct;
    QAction *newGameAct;

    QAction *runAct;
    QAction *stopAct;
    QAction *stepAct;
    QAction *replaceAct;
    QAction *xorAct;
    QAction *clearAct;
    QAction *impactAct;
    QAction *paramsAct;

    QAction *aboutAct;

    QTimer* timer;
    const static int defaultDelay = 1000;

    bool isRun = false;
    bool isXOR = false;
};

#endif // VIEW_H
