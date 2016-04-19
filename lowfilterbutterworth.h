#ifndef FILTERBUTTERWORTH_H
#define FILTERBUTTERWORTH_H

#include "filter.h"

class LowFilterButterworth: public Filter {
public:
    LowFilterButterworth(float cutoffFreq, float samplingFreq);
};

#endif // FILTERBUTTERWORTH_H
