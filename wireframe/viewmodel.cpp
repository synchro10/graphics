#include "viewmodel.h"

ViewModel::ViewModel()
{

}

void ViewModel::init(View *view, Model *model)
{
    this->view = view;
    this->model = model;
    this->area = view->getArea();
    this->options = view->getOptionsDiagog();
}

void ViewModel::createConnects()
{
    connect(view, &View::openFile, model, &Model::openFileHandle);
    connect(area, &DrawingArea::mouseMove, model, &Model::mouseMoveHandle);
    connect(area, &DrawingArea::wheelMove, model, &Model::wheelMoveHandle);
    connect(model, &Model::sendFrame, area, &DrawingArea::getFrame);
}
