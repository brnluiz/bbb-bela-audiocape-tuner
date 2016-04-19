/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

#include "lowfilterbutterworth.h"
#include "filter.h"
#include <cmath>

LowFilterButterworth::LowFilterButterworth(float cutoffFreq, float samplingFreq): Filter(2, cutoffFreq, samplingFreq) {
    const float c = 2 * sampling_;
    const float d = c * 1.4142;
    const float w = 2 * M_PI * cutoff_;

    // Parameters calcs
    a_[0] = pow(c,2) + d*w + pow(w,2);
    a_[1] = (2*pow(w,2) - 2*pow(c,2));
    a_[2] = (pow(c,2) - d*w + pow(w,2));

    b_[0] = (pow(w,2));
    b_[1] = (2*pow(w,2));
    b_[2] = (pow(w,2));

    // Divide all parameters by the common factor of a0
    for(int i = 0; i < size_; i++) {
        b_[i]  = b_[i]/a_[0];

        if(i != 0) {
            a_[i]  = a_[i]/a_[0];
        }
    }

    // Divide the a[0]
    a_[0] = 1;
}
