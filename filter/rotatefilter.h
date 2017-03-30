#ifndef ROTATEFILTER_H
#define ROTATEFILTER_H

#include "filter.h"
#include <iostream>

class RotateFilter : public Filter
{
public:
    RotateFilter(int angle);
    void processImage() override;
private:
    int angle = 0;
    bool belong(int i, int j);
};

#endif // ROTATEFILTER_H
