#include "view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(DEFAULT_WIDTH, DEFAULT_HEIGHT);
    area = new DrawingArea(this);
    setCentralWidget(area);
    createActions();
    createMenus();
    createToolbar();
    configureDialogs();
}

View::~View()
{

}

void View::open()
{
    QString initialPath = QDir::currentPath() + "/Data/";
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Open File"), initialPath);
    if (!fileName.isNull())
        emit openFile(fileName);
}

void View::spline()
{
    emit changeState();
}

void View::init()
{
    emit reset();
}

void View::showOptions()
{
    optionsDiagog->show();
}

void View::about()
{
    QMessageBox::about(this, tr("About App"),
                       tr("Kondratyev 14202"));
}

void View::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    splineAct = new QAction(tr("&Spline"), this);
    connect(splineAct, SIGNAL(triggered()), this, SLOT(spline()));

    initAct = new QAction(tr("&Init"), this);
    connect(initAct, SIGNAL(triggered()), this, SLOT(init()));

//    saveAct = new QAction(tr("&Save"), this);
//    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    optionAct = new QAction(tr("&Options"), this);
    connect(optionAct, SIGNAL(triggered()), this, SLOT(showOptions()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void View::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(optionAct);
    fileMenu->addAction(splineAct);
    fileMenu->addAction(initAct);
//    fileMenu->addAction(saveAct);
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
//    toolbar->addAction(saveAct);
    toolbar->addSeparator();
    toolbar->addAction(splineAct);
    toolbar->addAction(initAct);
    toolbar->addAction(optionAct);
    toolbar->addSeparator();
    toolbar->addAction(aboutAct);

    this->addToolBar(toolbar);
    this->addToolBarBreak();
}

void View::configureDialogs()
{
    optionsDiagog = new OptionsDialog(this);
}

OptionsDialog *View::getOptionsDiagog() const
{
    return optionsDiagog;
}

DrawingArea *View::getArea() const
{
    return area;
}
