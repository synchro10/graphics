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
}

void View::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Save"), this);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    selectAct = new QAction(tr("&Select"), this);
    connect(selectAct, SIGNAL(triggered()), this, SLOT(select()));
}

void View::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);

    editMenu = new QMenu(tr("&Edit"), this);
    editMenu->addAction(selectAct);

    filterMenu = new QMenu(tr("&Filter"), this);
    //filterMenu->addAction(filterMenu);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(editMenu);
    menuBar()->addMenu(filterMenu);
    menuBar()->addMenu(helpMenu);
}

void View::createToolbar()
{
    toolbar = new QToolBar(this);

    toolbar->addAction(openAct);
    toolbar->addAction(saveAct);
    toolbar->addSeparator();
    toolbar->addAction(selectAct);
    toolbar->addSeparator();
    toolbar->addSeparator();
    toolbar->addAction(aboutAct);

    this->addToolBar(toolbar);
}

void View::open()
{
    QString initialPath = QDir::currentPath() + "/Data/";
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Open File"), initialPath);
    area->open(fileName);
}

void View::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    action->setData(QVariant("png"));
    QByteArray fileFormat = action->data().toByteArray();

    QString initialPath = QDir::currentPath() + "/Data/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    //todo save
}

void View::about()
{
    QMessageBox::about(this, tr("About App"),
                       tr("Kondratyev 14202"));
}

void View::select()
{
    area->select();
}
