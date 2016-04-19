#ifndef FILTERFACTORY_H
#define FILTERFACTORY_H

#include "filter.h"
#include <string>

class FilterFactory
{
public:
    FilterFactory(float sampleFreq);
    Filter *make(std::string filter, float cutoffFreq);

private:
    float sampleFreq_;
};

#endif // FILTERFACTORY_H
