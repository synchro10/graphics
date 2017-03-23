#ifndef MYDOUBLESPINBOX_H
#define MYDOUBLESPINBOX_H

#include <QDoubleSpinBox>

class MyDoubleSpinBox : public QDoubleSpinBox
{
public:
    MyDoubleSpinBox(QObject *parent);
public slots:
    void setIntValue(int v);
};

#endif // MYDOUBLESPINBOX_H
