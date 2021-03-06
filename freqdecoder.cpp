/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

#include "freqdecoder.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

#include <string>
#include <stdexcept>
#include <iostream>

FreqDecoder::FreqDecoder() {
    int tableSize = sizeof(NotesParameters)*(NUM_NOTES*NUM_OCTAVES + 2);
    table_ = (NotesParameters *) malloc(tableSize);

    NotesParameters notes[] = {
        {0, "C",  16.35, 0},
        {1, "C#", 17.32, 0},
        {2, "D",  18.35, 0},
        {3, "Eb", 19.45, 0},
        {4, "E",  20.60, 0},
        {5, "F",  21.83, 0},
        {6, "F#", 23.12, 0},
        {7, "G",  24.50, 0},
        {8, "G#", 25.96, 0},
        {9, "A",  27.50, 0},
        {10, "Bb", 29.14, 0},
        {11, "B",  30.87, 0},
        
        {0, "C",  32.70, 1},
        {1, "C#", 34.65, 1},
        {2, "D",  36.71, 1},
        {3, "Eb", 38.89, 1},
        {4, "E",  41.20, 1},
        {5, "F",  43.65, 1},
        {6, "F#", 46.25, 1},
        {7, "G",  49.00, 1},
        {8, "G#", 51.91, 1},
        {9, "A",  55.00, 1},
        {10, "Bb", 58.27, 1},
        {11, "B",  61.74, 1},

        {0, "C",  65.41, 2},
        {1, "C#", 69.30, 2},
        {2, "D",  73.42, 2},
        {3, "Eb", 77.78, 2},
        {4, "E",  82.41, 2},
        {5, "F",  87.31, 2},
        {6, "F#", 92.50, 2},
        {7, "G",  98.00, 2},
        {8, "G#", 103.8, 2},
        {9, "A",  110.0, 2},
        {10, "Bb", 116.5, 2},
        {11, "B",  123.5, 2},

        {0, "C",  130.8, 3},
        {1, "C#", 138.6, 3},
        {2, "D",  146.8, 3},
        {3, "Eb", 155.6, 3},
        {4, "E",  164.8, 3},
        {5, "F",  174.6, 3},
        {6, "F#", 185.0, 3},
        {7, "G",  196.0, 3},
        {8, "G#", 207.7, 3},
        {9, "A",  220.0, 3},
        {10, "Bb", 233.1, 3},
        {11, "B",  246.9, 3},

        {0, "C",  261.6, 4},
        {1, "C#", 277.2, 4},
        {2, "D",  293.7, 4},
        {3, "Eb", 311.1, 4},
        {4, "E",  329.6, 4},
        {5, "F",  349.2, 4},
        {6, "F#", 370.0, 4},
        {7, "G",  392.0, 4},
        {8, "G#", 415.3, 4},
        {9, "A",  440.0, 4},
        {10, "Bb", 466.2, 4},
        {11, "B",  493.9, 4},

        {0, "C",  523.3, 5},
        {1, "C#", 554.4, 5},
        {2, "D",  587.3, 5},
        {3, "Eb", 622.3, 5},
        {4, "E",  659.3, 5},
        {5, "F",  698.5, 5},
        {6, "F#", 740.0, 5},
        {7, "G",  784.0, 5},
        {8, "G#", 830.0, 5},
        {9, "A",  880.0, 5},
        {10, "Bb", 932.3, 5},
        {11, "B",  987.8, 5},

        {0, "C",  1047, 6},
        {1, "C#", 1109, 6},
        {2, "D",  1175, 6},
        {3, "Eb", 1245, 6},
        {4, "E",  1319, 6},
        {5, "F",  1397, 6},
        {6, "F#", 1480, 6},
        {7, "G",  1568, 6},
        {8, "G#", 1661, 6},
        {9, "A",  1760, 6},
        {10, "Bb", 1865, 6},
        {11, "B",  1976, 6},

        {0, "C",  2093, 7},
        {1, "C#", 2217, 7},
        {2, "D",  2349, 7},
        {3, "Eb", 2489, 7},
        {4, "E",  2637, 7},
        {5, "F",  2794, 7},
        {6, "F#", 2960, 7},
        {7, "G",  3136, 7},
        {8, "G#", 3322, 7},
        {9, "A",  3520, 7},
        {10, "Bb", 3729, 7},
        {11, "B",  3951, 7},

        {0, "C",  4186, 8},
        {1, "C#", 4435, 8},
        {2, "D",  4699, 8},
        {3, "Eb", 4978, 8},
        {4, "E",  5274, 8},
        {5, "F",  5588, 8},
        {6, "F#", 5920, 8},
        {7, "G",  6272, 8},
        {8, "G#", 6645, 8},
        {9, "A",  7040, 8},
        {10, "Bb", 7459, 8},
        {11, "B",  7902, 8},
    };

    memcpy(table_, notes, tableSize);
}

NotesParameters FreqDecoder::get(float freq) {
    for(int i = 0; i < NUM_OCTAVES*NUM_NOTES; i++) {
        float value      = table_[i].freq;
        float lowMargin  = value * (1 - F_TOLERANCE);
        float highMargin = value * (1 + F_TOLERANCE);

        if(freq >= lowMargin && freq <= highMargin) {
            return table_[i];
        }
    }

    throw std::runtime_error("No note detected for this frequency");
}

std::string FreqDecoder::getNote(float freq) {
    return std::string(get(freq).name);
}

int FreqDecoder::getOctave(float freq) {
    return get(freq).octave;
}

float FreqDecoder::getFreq(float freq) {
    return get(freq).freq;
}
