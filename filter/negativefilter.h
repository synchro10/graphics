#ifndef NEGATIVEFILTER_H
#define NEGATIVEFILTER_H

#include <filter.h>
#include <iostream>

class NegativeFilter : public Filter
{
public:
    NegativeFilter();
    void processImage() override;

};

#endif // NEGATIVEFILTER_H
