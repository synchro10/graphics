#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include <QtWidgets>

class ControlPanel : public QWidget
{
    Q_OBJECT
public:
    explicit ControlPanel(QWidget *parent = 0);

    void setup();
signals:

public slots:
};

#endif // CONTROLPANEL_H
