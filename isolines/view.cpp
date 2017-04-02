#include "view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(520, 650);
    area = new DrawingArea(this);
    setCentralWidget(area);
    createActions();
    createMenus();
    createToolbar();
}

void View::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void View::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(exitAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(helpMenu);
}

void View::createToolbar()
{
    toolbar = new QToolBar(this);

    toolbar->addAction(openAct);
    toolbar->addSeparator();
    toolbar->addSeparator();
    toolbar->addAction(aboutAct);

    this->addToolBar(toolbar);
    this->addToolBarBreak();
}

void View::open()
{
    QString initialPath = QDir::currentPath() + "/Data/";
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Open File"), initialPath);
    if (!fileName.isNull())
        area->open(fileName);
}

void View::about()
{
    QMessageBox::about(this, tr("About App"),
                       tr("Kondratyev 14202"));
}
