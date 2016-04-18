#ifndef PEAKDATA_H
#define PEAKDATA_H

struct PeakData {
    float autoCorr;
    int   period;
    float freq;

    PeakData(): autoCorr(0), period(0), freq(0) {};
};

#endif // PEAKDATA_H
