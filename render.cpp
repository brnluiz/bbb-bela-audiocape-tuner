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
#include "settings.h"

// setup() is called once before the audio rendering starts.
// Use it to perform any initialisation and allocation which is dependent
// on the period size or sample rate.
//
// userData holds an opaque pointer to a data structure that was passed
// in from the call to initAudio().
//
// Return true on success; returning false halts the program.

CyclicBuffer* buffer;
Average* average;

bool setup(BeagleRTContext *context, void *userData)
{
    buffer = new CyclicBuffer(BUFFER_SIZE);
    average = new Average();

    average->insert(2);
    average->insert(0);
    average->insert(4);
    average->insert(0);
    average->insert(4);

	return true;
}

// render() is called regularly at the highest priority by the audio engine.
// Input and output are given from the audio hardware and the other
// ADCs and DACs (if available). If only audio is available, numMatrixFrames
// will be 0.
float detectFrequency(CyclicBuffer *samples, int sampleFreq)
{
    float sum             = 0;
    float sumOld          = 0;
    int thresh            = 0;
    PeakDetectState state = PEAKDETECT_INITIAL;
    int detectedPeriod    = 0;
    int windowSize        = samples->getSize();

    // Autocorrelation WITH Peak Detection
    for (int i = 0; i < windowSize && (state != PEAKDETECT_FOUND); i++) {
        sumOld = sum;
        sum = 0;

        // Auto-correlation Core
        for (int k = 0; k < windowSize-i; k++) {
            sum += samples->get(k) * samples->get(k+i);
        }

        // Peak Detect State Machine
        switch (state) {
            case PEAKDETECT_INITIAL:
                thresh = sum / 2;
                state = PEAKDETECT_POSITIVE;
                break;

            case PEAKDETECT_POSITIVE:
                if ( (sum > thresh) && (sum - sumOld) > 0 ) {
                    state = PEAKDETECT_NEGATIVE;
                }
                break;

            case PEAKDETECT_NEGATIVE:
                if ((sum - sumOld) <= 0) {
                    detectedPeriod = i;
                    state = PEAKDETECT_FOUND;
                }
                break;

            default:
                break;
        }
    }

    if (detectedPeriod < 1) {
      return 0;
    }

    return sampleFreq/detectedPeriod;
}

void render(BeagleRTContext *context, void *userData)
{
	for(unsigned int n = 0; n < context->audioFrames; n++) {
		// Get the input
		float input = (context->audioIn[n*context->audioChannels] + context->audioIn[n*context->audioChannels+1]) * 0.5;

        if(buffer->isFilled()) {
            float freq = detectFrequency(buffer, context->audioSampleRate);
            printf("Frequency: %f\n", freq);
//            average->insert(freq);

            buffer->reset(true);
        }

        buffer->insert(input);

	}

//    if(average->getSize() >= 5) {
//        printf("Frequency: %f | size: %i\n", average->arithmetic(), average->getSize());
//        average->reset();
//    }
}

// cleanup_render() is called once at the end, after the audio has stopped.
// Release any resources that were allocated in initialise_render().

void cleanup(BeagleRTContext *context, void *userData)
{
	/* TASK:
	 * If you allocate any memory, be sure to release it here.
	 * You may or may not need anything in this function, depending
	 * on your implementation.
	 */
    delete buffer;
}
