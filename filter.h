/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

#ifndef FILTER_H
#define FILTER_H

class Filter {
public:
    Filter(float order, float cutoffFreq, float samplingFreq);
    ~Filter();

    void setOrder(int order);
    void reset();

    float run(float sample);

    bool setParam(char param, int idx, float value);
    float getParam(char param, int idx);

protected:
    int order_;
    int size_;

    float* a_;
    float* b_;

    float* x_;
    float* y_;

    float cutoff_;
    float sampling_;
};

#endif // FILTER_H
