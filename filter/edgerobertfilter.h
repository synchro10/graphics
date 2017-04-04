#ifndef EDGEROBERTFILTER_H
#define EDGEROBERTFILTER_H

#include "filter.h"
#include <iostream>
#include <QImage>

class EdgeRobertFilter : public Filter
{
public:
    EdgeRobertFilter(int value);
    void processImage() override;
private:
    int threshold = 20;
};

#endif // EDGEROBERTFILTER_H
