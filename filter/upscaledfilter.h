#ifndef UPSCALEDFILTER_H
#define UPSCALEDFILTER_H

#include "filter.h"
#include "iostream"

class UpscaledFilter : public Filter
{
public:
    UpscaledFilter();
    void processImage() override;
};

#endif // UPSCALEDFILTER_H
