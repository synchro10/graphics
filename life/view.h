#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include "field.h"

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
    ~View();
    Field *getField() const;
    void setField(Field *value);

private:
    Field* field;
};

#endif // VIEW_H
