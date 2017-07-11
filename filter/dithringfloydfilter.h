#ifndef DITHRINGFLOYDFILTER_H
#define DITHRINGFLOYDFILTER_H

#include "filter.h"

class DithringFloydFilter : public Filter
{
public:
    DithringFloydFilter(int red, int green, int blue);
    void processImage() override;
private:
    int getNearColor(int color, int division);
    int red = 4;
    int green = 4;
    int blue = 4;
};

#endif // DITHRINGFLOYDFILTER_H
