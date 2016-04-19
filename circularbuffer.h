/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H

class CircularBuffer {
public:
    CircularBuffer(int bufferSize);
    ~CircularBuffer();

    bool insert(float item);
    float get(int pos);
    bool isFilled();

    void setSize(int size);
    int  getSize();

    void reset(bool fast = false);
protected:
    bool filled_;
    int idx_;
    float *buffer_;
    int size_;
};

#endif // CYCLICBUFFER_H
