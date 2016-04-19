/*
 * assignment1_crossover
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * First assignment for ECS732 RTDSP, to implement a 2-way audio crossover
 * using the BeagleBone Black.
 *
 * Andrew McPherson and Victor Zappi
 * Modified by Becky Stewart
 * Queen Mary, University of London
 */

#include <BeagleRT.h>
#include <cmath>
#include <rtdk.h>
#include "cyclicbuffer.h"
#include "lowfilterbutterworth.h"
#include "settings.h"
#include "appparameters.h"
#include "freqdecoder.h"
#include "peakdata.h"

#include <iostream>
#include <string>

CyclicBuffer* buffer;
LowFilterButterworth* filter;
FreqDecoder* freqDecoder;

bool setup(BeagleRTContext *context, void *userData) {
    // Get the params and print them
    Parameters params = *(Parameters *)userData;
    printf("Filter frequency: %f | Buffer size: %f\n", params.filterFreq, params.bufferSize);

    try {
        // Allocate dynamic variables (don't forget to remove them at cleanup() )
        buffer      = new CyclicBuffer(params.bufferSize);
        filter      = new LowFilterButterworth(params.filterFreq, context->audioSampleRate);
        freqDecoder = new FreqDecoder();

    } catch( const std::exception& e ) {
       // information from the error
        std::cerr << "[exception] " << e.what() << std::endl;
        return false;
    }

    return true;
}

float autoCorr(CyclicBuffer *samples, int lag) {
    float sum = 0;
    int windowSize = samples->getSize();

    // Auto-correlation Core
    for (int k = 0; k < (windowSize - lag); k++) {
        sum += samples->get(k) * samples->get(k+lag);
    }

    return sum;
}

float detectFrequency(CyclicBuffer *samples, int sampleFreq) {
    float sum             = 0;
    float sumOld          = 0;
    int thresh            = 0;
    PeakDetectState state = PEAKDETECT_INITIAL;
    int detectedPeriod    = 0;
    int windowSize        = samples->getSize();

    float threshAutoCorr = 10.00;

    // Will save the detected frequencies + the auto correlation index
    int peaksIdx            = 0;
    const int peakFreqsSize = 8;
    PeakData peaksData[peakFreqsSize];

    for (int i = 0; i < windowSize && (state != PEAKDETECT_FINAL); i++) {
        sumOld = sum;

        // Auto-correlation
        sum = autoCorr(samples, i);

        // Peak Detect State Machine
        switch (state) {
            case PEAKDETECT_INITIAL:
                thresh = sum * .5;
                state = PEAKDETECT_POSITIVE;
                break;

            case PEAKDETECT_POSITIVE:
                if ((sum > thresh) && (sum - sumOld) > 0) {
                    state = PEAKDETECT_NEGATIVE;
                }
                break;

            case PEAKDETECT_NEGATIVE:
                if ((sum - sumOld) <= 0) {
                    state = PEAKDETECT_FOUND;
                } else {
                    break;
                }
            case PEAKDETECT_FOUND:
                // If you already detected a good quantity of frequency peaks
                if (peaksIdx >= (peakFreqsSize-1)) {
                    state = PEAKDETECT_FINAL;
                    break;
                }
                // Save the info about the detected frequency peak
                peaksData[peaksIdx].period   = i;
                peaksData[peaksIdx].autoCorr = sum;
                peaksIdx++;

                state = PEAKDETECT_INITIAL;

            default:
                break;
        }
    }

    // Get the detected period based on the auto-correlation index
    int bestAutoCorrIdx = 0;
    for (int i = 0; i < peakFreqsSize; i++) {
        if(peaksData[i].autoCorr > peaksData[bestAutoCorrIdx].autoCorr) {
            bestAutoCorrIdx = i;
        }
    }
    // Protection against divisions by 0 and unwanted frequencies
    if (detectedPeriod < 1 && (peaksData[bestAutoCorrIdx].autoCorr < threshAutoCorr)) {
      return 0;
    }

    detectedPeriod = peaksData[bestAutoCorrIdx].period;

    return sampleFreq/detectedPeriod;
}

void render(BeagleRTContext *context, void *userData) {
    try {
        // Render logic for every audio frame
        for(unsigned int n = 0; n < context->audioFrames; n++) {
                // Get the input
                float input = (context->audioIn[n*context->audioChannels]
                        + context->audioIn[n*context->audioChannels+1]) * 0.5;

                // Filter the input based on the passed cut-off frequency
                float filtered = filter->run(input);

                // If the buffer is full, then detect the frequency (it needs a certain amount of
                // samples to work)
                if (buffer->isFilled()) {
                    float freq = detectFrequency(buffer, context->audioSampleRate);

                    // Output for the user
                    if (freq != 0) {
                        std::string note = freqDecoder->getNote(freq);
                        rt_printf("Frequency: %f | Note: %s\n", freq, note.c_str());
                    }
                    buffer->reset(true);
                }

                buffer->insert(filtered);
        }
    } catch( const std::exception& e ) {
        std::cerr << "[exception] " << e.what() << std::endl;
        return ;
    }
}

void cleanup(BeagleRTContext *context, void *userData) {
    delete buffer;
    delete filter;
    delete freqDecoder;
}
