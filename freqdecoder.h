/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

#ifndef FREQDECODER_H
#define FREQDECODER_H

#define NUM_NOTES   12
#define NUM_OCTAVES 9
#define F_TOLERANCE .03

#include <string>

struct NotesParameters {
    int id;
    char name[4];
    float freq;
    int octave;
};

class FreqDecoder {
public:
    FreqDecoder();
    NotesParameters get(float freq);

    std::string getNote(float freq);
    int getOctave(float freq);
    float getFreq(float freq);

private:
    NotesParameters* table_;
};

#endif // FREQDECODER_H
