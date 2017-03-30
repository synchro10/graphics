#ifndef WATERFILTER_H
#define WATERFILTER_H

#include "filter.h"
#include <iostream>

class WaterFilter : public Filter
{
public:
    WaterFilter();
    void processImage() override;

};

#endif // WATERFILTER_H
