#ifndef VIEWMODEL_H
#define VIEWMODEL_H

#include <QObject>
#include "view.h"
#include "model.h"
#include "drawingarea.h"
#include "optionsdialog.h"

class ViewModel : public QObject
{
    Q_OBJECT
public:
    ViewModel();
    void init(View*, Model*);
    void createConnects();
private:
    const View* view;
    const Model* model;
    const DrawingArea* area;
    const OptionsDialog* options;
};

#endif // VIEWMODEL_H
