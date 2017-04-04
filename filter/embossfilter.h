#ifndef EMBOSSFILTER_H
#define EMBOSSFILTER_H

#include "filter.h"
#include <iostream>

class EmbossFilter : public Filter
{
public:
    EmbossFilter();
    void processImage() override;
};

#endif // EMBOSSFILTER_H
