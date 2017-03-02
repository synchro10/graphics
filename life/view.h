#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QPushButton>
#include <QHBoxLayout>
#include <memory>
#include "field.h"

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
    ~View();
    Field *getField() const;

private:
    std::unique_ptr<Field> field;

    QScrollArea *scroll;
};

#endif // VIEW_H
