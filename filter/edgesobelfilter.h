#ifndef EDGESOBELFILTER_H
#define EDGESOBELFILTER_H

#include "filter.h"
#include <iostream>

class EdgeSobelFilter : public Filter
{
public:
    EdgeSobelFilter(int value);
    void processImage() override;
private:
    int threshold = 20;
};

#endif // EDGESOBELFILTER_H
