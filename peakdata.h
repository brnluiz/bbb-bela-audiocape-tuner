/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

#ifndef PEAKDATA_H
#define PEAKDATA_H

struct PeakData {
    float autoCorr;
    int   period;
    float freq;

    PeakData(): autoCorr(0), period(0), freq(0) {};
};

#endif // PEAKDATA_H
