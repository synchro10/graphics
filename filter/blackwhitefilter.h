#ifndef BLACKWHITEFILTER_H
#define BLACKWHITEFILTER_H

#include <filter.h>
#include <iostream>

class BlackWhiteFilter : public Filter
{
public:
    BlackWhiteFilter();
    void processImage() override;
};

#endif // BLACKWHITEFILTER_H
