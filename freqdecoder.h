#ifndef FREQDECODER_H
#define FREQDECODER_H

#define NUM_NOTES   12
#define NUM_OCTAVES 9

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
