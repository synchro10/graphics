#include "mydoublespinbox.h"

MyDoubleSpinBox::MyDoubleSpinBox(QObject *parent)
{
}

void MyDoubleSpinBox::setIntValue(int v)
{
    setValue(double(v)/10);
}
