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

    virtual void calcParams() {;}

    float cutoff_;
    float sampling_;
};

#endif // FILTER_H
