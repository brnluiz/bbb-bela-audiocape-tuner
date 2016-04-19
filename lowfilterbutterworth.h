/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

#ifndef FILTERBUTTERWORTH_H
#define FILTERBUTTERWORTH_H

#include "filter.h"

class LowFilterButterworth: public Filter {
public:
    LowFilterButterworth(float cutoffFreq, float samplingFreq);
};

#endif // FILTERBUTTERWORTH_H
