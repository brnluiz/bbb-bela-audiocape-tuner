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
