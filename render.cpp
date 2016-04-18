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
#include "average.h"
#include "lowfilterbutterworth.h"
#include "settings.h"
#include "appparameters.h"
#include "freqdecoder.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

CyclicBuffer* buffer;
LowFilterButterworth* filter;
FreqDecoder* freqDecoder;

bool setup(BeagleRTContext *context, void *userData) {
    // Get the params and print them
    Parameters params = *(Parameters *)userData;
    printf("Filter frequency: %f | Buffer size: %f\n", params.filterFreq, params.bufferSize);

    // Allocate dynamic variables (don't forget to remove them at cleanup() )
    buffer  = new CyclicBuffer(params.bufferSize);
    filter  = new LowFilterButterworth(params.filterFreq, context->audioSampleRate);
    freqDecoder = new FreqDecoder();

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

    const int peakFreqsSize = 8;

    int peakPeriods[peakFreqsSize] = {0};
    float autoCorrFreqs[peakFreqsSize] = {0};
    int peakFreqsIdx = 0;
    // Autocorrelation WITH Peak Detection
    for (int i = 0; i < windowSize; i++) {
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
                    if(peakFreqsIdx >= (peakFreqsSize-1)) {
                        state = PEAKDETECT_FINAL;
                        break;
                    }

                    peakPeriods[peakFreqsIdx] = i;
                    autoCorrFreqs[peakFreqsIdx] = sum;
                    peakFreqsIdx++;

                    state = PEAKDETECT_INITIAL;
                }
                break;

            default:
                break;
        }
    }

    int bestAutoCorrIdx = 0;
    for (int i = 0; i < peakFreqsSize; i++) {
        if(autoCorrFreqs[i] > autoCorrFreqs[bestAutoCorrIdx]) {
            bestAutoCorrIdx = i;
        }
    }
    detectedPeriod = peakPeriods[bestAutoCorrIdx];

    if (detectedPeriod < 1) {
      return 0;
    }

    return sampleFreq/detectedPeriod;
}

void render(BeagleRTContext *context, void *userData) {
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
                string note = freqDecoder->getNote(freq);
                rt_printf("Frequency: %f | Note: %s\n", freq, note.c_str());
            }
            buffer->reset(true);
        }

        buffer->insert(filtered);

	}
}

void cleanup(BeagleRTContext *context, void *userData) {
    delete buffer;
    delete filter;
    delete freqDecoder;
}
