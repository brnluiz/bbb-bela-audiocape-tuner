/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

#include "filterfactory.h"
#include "filter.h"
#include <string>
#include <stdexcept>

#include "lowfilterbutterworth.h"

FilterFactory::FilterFactory(float sampleFreq): sampleFreq_(sampleFreq) {
}

Filter *FilterFactory::make(std::string filter, float cutoffFreq) {
    if(filter == "low-butterworth") {
        return new LowFilterButterworth(cutoffFreq, sampleFreq_);
    } else {
        throw std::runtime_error("Requested filter not implemented");
    }
}
