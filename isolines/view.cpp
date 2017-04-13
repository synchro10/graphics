#include "view.h"

View::View(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(520, 700);
    area = new DrawingArea(this);
    setCentralWidget(area);
    createActions();
    createMenus();
    createToolbar();
    configureDialogs();
    statusBar()->setVisible(true);
    connect(area, &DrawingArea::statusMessage, [this](const QString& message){statusBar()->showMessage(message, 10000);});
}

void View::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    interpolateAct = new QAction(tr("&Interpolation"), this);
    connect(interpolateAct, SIGNAL(triggered()), this, SLOT(interpolation()));

    gridAct = new QAction(tr("&Grid"), this);
    connect(gridAct, SIGNAL(triggered()), this, SLOT(grid()));

    isolineAct = new QAction(tr("&Isoline"), this);
    connect(isolineAct, SIGNAL(triggered()), this, SLOT(isoline()));

    pointAct = new QAction(tr("&Points"), this);
    connect(pointAct, SIGNAL(triggered()), this, SLOT(point()));

    clearAct = new QAction(tr("&Clear"), this);
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clear()));

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
    fileMenu->addAction(interpolateAct);
    fileMenu->addAction(gridAct);
    fileMenu->addAction(isolineAct);
    fileMenu->addAction(pointAct);
    fileMenu->addAction(clearAct);
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
    toolbar->addAction(interpolateAct);
    toolbar->addAction(gridAct);
    toolbar->addAction(isolineAct);
    toolbar->addAction(pointAct);
    toolbar->addAction(clearAct);
    toolbar->addAction(optionAct);
    toolbar->addSeparator();
    toolbar->addAction(aboutAct);

    this->addToolBar(toolbar);
    this->addToolBarBreak();
}

void View::configureDialogs()
{
    optionsDiagog = new OptionsDialog(this);
    connect(optionsDiagog, SIGNAL(finished(Options)), this, SLOT(setOptions(Options)));
}

void View::open()
{
    QString initialPath = QDir::currentPath() + "/Data/";
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Open File"), initialPath);
    if (!fileName.isNull())
        area->open(fileName);
}

void View::interpolation()
{
    area->setInterpolation();
}

void View::grid()
{
    area->setGrid();
}

void View::isoline()
{
    area->setIsoline();
}

void View::point()
{
    area->setPoint();
}

void View::clear()
{
    area->clear();
}

void View::showOptions()
{
    optionsDiagog->init(area->getOptions());
    optionsDiagog->show();
}

void View::setOptions(const Options options)
{
    area->setOptions(options);
    optionsDiagog->close();
}

void View::about()
{
    QMessageBox::about(this, tr("About App"),
                       tr("Kondratyev 14202"));
}
