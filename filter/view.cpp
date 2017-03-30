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

    moveCAct = new QAction(tr("&<-Move"), this);
    connect(moveCAct, SIGNAL(triggered()), this, SLOT(moveFromC()));

    blackWhiteAct       = new QAction(tr("&Grey"), this);
    negativeAct         = new QAction(tr("&Negative"), this);
    ditheringAct        = new QAction(tr("&Dithering"), this);
    ditheringErrorAct   = new QAction(tr("&Dithering Error"), this);
    upscaleAct          = new QAction(tr("&Upscale"), this);
    rotateAct           = new QAction(tr("&Rotate"), this);
    gammaAct            = new QAction(tr("&Gamma"), this);
    edgeRobertAct       = new QAction(tr("&Edge Robert"), this);
    edgeSobelAct        = new QAction(tr("&Edge Sobel"), this);
    edgeSpecAct         = new QAction(tr("&Edge Spec"), this);
    embossAct           = new QAction(tr("&Emboss"), this);
    waterAct            = new QAction(tr("&Water"), this);
    blurAct             = new QAction(tr("&Blur"), this);
    sharpenAct          = new QAction(tr("&Sharpen"), this);
}

void View::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);

    editMenu = new QMenu(tr("&Edit"), this);
    editMenu->addAction(selectAct);
    editMenu->addAction(moveCAct);

    filterMenu = new QMenu(tr("&Filter"), this);
    filterMenu->addAction(blackWhiteAct);
    filterMenu->addAction(negativeAct);
//    filterMenu->addAction(ditheringAct     );
//    filterMenu->addAction(ditheringErrorAct);
    filterMenu->addAction(upscaleAct       );
    filterMenu->addAction(rotateAct        );
//    filterMenu->addAction(gammaAct         );
//    filterMenu->addAction(edgeRobertAct    );
//    filterMenu->addAction(edgeSobelAct     );
//    filterMenu->addAction(edgeSpecAct      );
//    filterMenu->addAction(embossAct        );
    filterMenu->addAction(waterAct         );
    filterMenu->addAction(blurAct          );
    filterMenu->addAction(sharpenAct       );

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
    filterToolbar = new QToolBar(this);

    toolbar->addAction(openAct);
    toolbar->addAction(saveAct);
    toolbar->addSeparator();
    toolbar->addAction(selectAct);
    toolbar->addAction(moveCAct);
    toolbar->addSeparator();
    toolbar->addAction(aboutAct);   

    filterToolbar->addAction(blackWhiteAct);
    filterToolbar->addAction(negativeAct);
//    filterToolbar->addAction(ditheringAct     );
//    filterToolbar->addAction(ditheringErrorAct);
    filterToolbar->addAction(upscaleAct       );
    filterToolbar->addAction(rotateAct        );
//    filterToolbar->addAction(gammaAct         );
//    filterToolbar->addAction(edgeRobertAct    );
//    filterToolbar->addAction(edgeSobelAct     );
//    filterToolbar->addAction(edgeSpecAct      );
//    filterToolbar->addAction(embossAct        );
    filterToolbar->addAction(waterAct         );
    filterToolbar->addAction(blurAct          );
    filterToolbar->addAction(sharpenAct       );

    this->addToolBar(toolbar);
    this->addToolBarBreak();
    this->addToolBar(filterToolbar);
}

void View::open()
{
    QString initialPath = QDir::currentPath() + "/Data/";
    QString fileName = QFileDialog::getOpenFileName(this,
                                tr("Open File"), initialPath);
    if (!fileName.isNull())
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
    if (!fileName.isNull())
        area->save(fileName);
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

void View::moveFromC()
{
    area->moveFromC();
}

void View::setImageC(QImage *image)
{
    area->setCImage(image);
}

QImage *View::getImageB()
{
    return area->getImageB();
}

void View::setControl(QWidget *controlWidget)
{
    area->setControlPanel(controlWidget);
}
