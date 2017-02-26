#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>

class View : public QMainWindow
{
    Q_OBJECT

public:
    View(QWidget *parent = 0);
    ~View();
};

#endif // VIEW_H
