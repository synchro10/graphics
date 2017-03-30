#ifndef BLURFILTER_H
#define BLURFILTER_H

#include "filter.h"
#include <iostream>

class BlurFilter : public Filter
{
public:
    BlurFilter();
    void processImage() override;
};

#endif // BLURFILTER_H
