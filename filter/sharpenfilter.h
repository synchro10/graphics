#ifndef SHARPENFILTER_H
#define SHARPENFILTER_H

#include <iostream>
#include "filter.h"

class SharpenFilter : public Filter
{
public:
    SharpenFilter();

    void processImage() override;
private:

};

#endif // SHARPENFILTER_H
