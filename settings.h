/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

#ifndef SETTINGS_H
#define SETTINGS_H

#define BUFFER_SIZE 2048
#define FILTER_FREQ 400

#define THRESHOLD_AUTOCORR  10.00
#define PEAKS_BUFFER_SIZE   8

typedef enum {
    PEAKDETECT_INITIAL,
    PEAKDETECT_POSITIVE,
    PEAKDETECT_NEGATIVE,
    PEAKDETECT_FOUND,
    PEAKDETECT_FINAL,
} PeakDetectState;

#endif // SETTINGS_H
