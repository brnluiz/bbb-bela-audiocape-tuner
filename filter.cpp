/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

#include "filter.h"
#include <cstdlib>
#include <cstdio>

#include <stdexcept>

Filter::Filter(float order, float cutoffFreq, float samplingFreq):
    order_(order), cutoff_(cutoffFreq), sampling_(samplingFreq) {
    setOrder(order);
}

Filter::~Filter(){
    free(a_);
    free(b_);
    free(x_);
    free(y_);
}

void Filter::setOrder(int order) {
    free(a_);
    free(b_);
    free(x_);
    free(y_);

    order_ = order;
    size_ = order_+1;

    a_ = (float *) malloc(sizeof(float)*(size_+1));
    b_ = (float *) malloc(sizeof(float)*(size_+1));
    x_ = (float *) malloc(sizeof(float)*(size_+1));
    y_ = (float *) malloc(sizeof(float)*(size_+1));

    if(a_ == NULL || b_ == NULL || x_ == NULL || y_ == NULL) {
        throw std::bad_alloc();
    }

    for(int i = 0; i < size_; i++) {
        a_[i] = 0;
        b_[i] = 0;
        x_[i] = 0;
        y_[i] = 0;
    }
}

void Filter::reset(){
    for(int i = 0; i < size_; i++) {
        x_[i] = 0;
        y_[i] = 0;
    }
}

float Filter::run(float sample) {
    if(cutoff_ == 0) {
        return sample;
    }

    float out = 0;

    // Create the filter_ output
    for(int i = 1; i <= order_; i++) {
        out += b_[i] * x_[i-1];
        out -= a_[i] * y_[i-1];
    }
    out += b_[0] * sample;

    // Save data for later
    for (int i = 1; i < order_; i++) {
        x_[i] = x_[i-1];
        y_[i] = y_[i-1];
    }
    x_[0] = sample;
    y_[0] = out;

    return out;
}

bool Filter::setParam(char param, int idx, float value)
{
    if(idx > order_) {
        throw std::out_of_range("'idx' is out of range");
    }

    switch (param) {
        case 'a':
            a_[idx] = value;
            break;
        case 'b':
            b_[idx] = value;
            break;
        case 'x':
            x_[idx] = value;
            break;
        case 'y':
            y_[idx] = value;
            break;
        default:
            throw std::invalid_argument("'param' is not a valid argument");
    }

    return true;
}

float Filter::getParam(char param, int idx) {
    if(idx > order_) {
        throw std::out_of_range("'idx' is out of range");
    }

    switch (param) {
        case 'a':
            return a_[idx];
            break;
        case 'b':
            return b_[idx];
        case 'x':
            return x_[idx];
        case 'y':
            return y_[idx];
        default:
            throw std::invalid_argument("'param' is not a valid argument");
    }
}
