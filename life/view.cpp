#include "view.h"
#include <QtWidgets>
#include <iostream>
#include "controller.h"

View::View(QWidget *parent)
    : QMainWindow(parent), scroll(new QScrollArea)
{    
    field = std::unique_ptr<Field>(new Field(this));

    createActions();
    createMenus();
    createToolbar();

    timer = new QTimer(this);
    timer->setInterval(defaultDelay);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextIteration()));

    scroll->setWidget(field.get());
    setCentralWidget(scroll);

    startGameDialog = new NewGameDiagog(this);
    options = new Options(this);
    configDialogs();
    resize(800, 600);
}

Field *View::getField() const
{
    return field.get();
}



void View::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    saveAct = new QAction(tr("&Save"), this);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(save()));

    newGameAct = new QAction(tr("&New Game"), this);
    connect(newGameAct, SIGNAL(triggered()), this, SLOT(newGame()));

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    runAct = new QAction(tr("&Run"), this);
    connect(runAct, SIGNAL(triggered()), this, SLOT(run()));

    stopAct = new QAction(tr("&Stop"), this);
    stopAct->setDisabled(true);
    connect(stopAct, SIGNAL(triggered()), this, SLOT(stop()));

    stepAct = new QAction(tr("&Step"), this);
    connect(stepAct, SIGNAL(triggered()), this, SLOT(nextIteration()));

    replaceAct = new QAction(tr("&Replace"), this);
    replaceAct->setDisabled(true);
    connect(replaceAct, SIGNAL(triggered()), this, SLOT(replaceMode()));

    xorAct = new QAction(tr("&XOR"), this);
    connect(xorAct, SIGNAL(triggered()), this, SLOT(xorMode()));

    clearAct = new QAction(tr("&Clear"), this);
    connect(clearAct, SIGNAL(triggered()), this, SLOT(clearField()));

    impactAct = new QAction(tr("&Show impacts"), this);
    connect(impactAct, SIGNAL(triggered()), this, SLOT(impact()));

    paramsAct = new QAction(tr("&Change options"), this);
    connect(paramsAct, SIGNAL(triggered()), this, SLOT(params()));

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));
}

void View::createMenus()
{

    fileMenu = new QMenu(tr("&File"), this);
    fileMenu->addAction(newGameAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    optionMenu = new QMenu(tr("&Game"), this);
    optionMenu->addAction(runAct);
    optionMenu->addAction(stepAct);
    optionMenu->addAction(replaceAct);
    optionMenu->addAction(xorAct);
    optionMenu->addAction(clearAct);
    optionMenu->addAction(impactAct);
    optionMenu->addAction(paramsAct);

    helpMenu = new QMenu(tr("&Help"), this);
    helpMenu->addAction(aboutAct);

    menuBar()->addMenu(fileMenu);
    menuBar()->addMenu(optionMenu);
    menuBar()->addMenu(helpMenu);

}

void View::createToolbar()
{
    toolbar = new QToolBar(this);

    toolbar->addAction(newGameAct);
    toolbar->addAction(openAct);
    toolbar->addAction(saveAct);
    toolbar->addSeparator();
    toolbar->addAction(runAct);
    toolbar->addAction(stopAct);
    toolbar->addAction(stepAct);
    toolbar->addAction(replaceAct);
    toolbar->addAction(xorAct);
    toolbar->addAction(clearAct);
    toolbar->addAction(impactAct);
    toolbar->addAction(paramsAct);
    toolbar->addAction(aboutAct);

    this->addToolBar(toolbar);
}

void View::configDialogs()
{
    connect(startGameDialog->button, SIGNAL(accepted()), this,
            SLOT(startGame()));
    connect(options->button, SIGNAL(accepted()), this,
            SLOT(setOptions()));
}

void View::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        event->accept();
    } else {
        event->ignore();
    }
}

void View::open()
{
    QString initialPath = QDir::currentPath() + "/Data/";
    if (maybeSave()) {
        QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open File"), initialPath);
        uint cellSize = model->initFromFile(fileName);
        if (0 != cellSize){
            field->changeParam(model->getGridWidth(), model->getGridHeight(), cellSize);
        }
        model->countNextState();
    }
}

void View::save()
{
    QAction *action = qobject_cast<QAction *>(sender());
    action->setData(QVariant("txt"));
    QByteArray fileFormat = action->data().toByteArray();
    saveFile(fileFormat);
}

void View::about()
{
    QMessageBox::about(this, tr("About App"),
                       tr("Kondratyev 14202"));
}

void View::startGame()
{
    //uint width, uint height, int cellSize
    uint width = startGameDialog->sliderM->value();
    uint height = startGameDialog->sliderN->value();
    uint cellSize = startGameDialog->sliderC->value();
    model->resize(width, height);
    field->changeParam(model->getGridWidth(), model->getGridHeight(), cellSize);

    startGameDialog->close();
    clearField();
}

void View::nextIteration()
{
    model->countNextState();
    model->changeState();
    model->countNextState();
    field->setField(&model->getCurrentState());
    field->update();
}

void View::run()
{
    if (!isRun){
        timer->start();
        isRun = true;
        runAct->setDisabled(true);
        stopAct->setEnabled(true);
    }
}

void View::stop()
{
    if (isRun){
        timer->stop();
        isRun = false;
        stopAct->setDisabled(true);
        runAct->setEnabled(true);
    }
}

void View::clearField()
{
    stop();
    model->clear();
    field->setField(&model->getCurrentState());
    field->update();
}

void View::replaceMode()
{
    isXOR = false;
    field->isXOR = false;
    replaceAct->setDisabled(true);
    xorAct->setEnabled(true);
}

void View::xorMode()
{
    isXOR = true;
    field->isXOR = true;
    xorAct->setDisabled(true);
    replaceAct->setEnabled(true);
}

void View::impact()
{
    field->isShowImpact = !field->isShowImpact;
    field->update();
}

void View::params()
{
    stop();
    options->show();
}

void View::newGame()
{
    stop();
    startGameDialog->show();
}

void View::setModel(Model *value)
{
    model = value;
}


bool View::maybeSave()
{
    return true;
}

bool View::saveFile(const QByteArray &fileFormat)
{
    QString initialPath = QDir::currentPath() + "/untitled." + fileFormat;

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
                               initialPath,
                               tr("%1 Files (*.%2);;All Files (*)")
                               .arg(QString::fromLatin1(fileFormat.toUpper()))
                               .arg(QString::fromLatin1(fileFormat)));
    model->saveToFile(fileName, field->getCellSize());
}

void View::setOptions()
{
    uint width = options->sliderM->value();
    uint height = options->sliderN->value();
    uint cellSize = options->sliderC->value();
    model->resize(width, height);
    field->changeParam(model->getGridWidth(), model->getGridHeight(), cellSize);

    uint LIVE_BEGIN = options->sliderLiveB->value();
    uint LIVE_END = options->sliderBirthE->value();
    uint BIRTH_BEGIN = options->sliderBirthB->value();
    uint BIRTH_END = options->sliderBirthE->value();
    uint FST_IMPACT = options->sliderFstI->value();
    uint SND_IMPACT = options->sliderSndI->value();
    //tmp
    options->spinBoxLiveB   ->setValue(LIVE_BEGIN/10);
    options->spinBoxBirthE   ->setValue(LIVE_END/10);
    options->spinBoxBirthB   ->setValue(BIRTH_BEGIN/10);
    options->spinBoxBirthE   ->setValue(LIVE_BEGIN/10);
    options->spinBoxFstI   ->setValue(FST_IMPACT/10);
    options->spinBoxSndI   ->setValue(SND_IMPACT/10);

    if( model->changeRules(LIVE_BEGIN, LIVE_END, BIRTH_BEGIN, BIRTH_END, FST_IMPACT, SND_IMPACT)){
        model->countNextState();
    }

    options->close();
    update();
}

