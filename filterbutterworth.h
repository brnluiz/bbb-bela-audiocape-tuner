#ifndef FILTERBUTTERWORTH_H
#define FILTERBUTTERWORTH_H

#include "filter.h"

class FilterButterworth: public Filter {
public:
    FilterButterworth(float cutoffFreq, float samplingFreq);
protected:
    void calcParams();
};

#endif // FILTERBUTTERWORTH_H
