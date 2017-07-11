#ifndef GAMMAFILTER_H
#define GAMMAFILTER_H

#include "filter.h"
#include "QImage"

class GammaFilter : public Filter
{
public:
    GammaFilter(double value);
    void processImage() override;
private:
    double gamma = 1.0;
};

#endif // GAMMAFILTER_H
