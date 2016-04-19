/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

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
