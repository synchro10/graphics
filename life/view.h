#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include <QList>
#include <QMenu>
#include <QToolBar>
#include <memory>
#include "field.h"

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
    ~View(){}
    Field *getField() const;

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private slots:
    void open();
    void save();
    void about();

private:
    std::unique_ptr<Field> field;

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
};

#endif // VIEW_H
