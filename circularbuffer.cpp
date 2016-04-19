/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

#include "circularbuffer.h"
#include <cstdlib>
#include <cstdio>

#include <stdexcept>

CircularBuffer::CircularBuffer(int bufferSize): filled_(false), idx_(0), size_(bufferSize) {
    setSize(bufferSize);
}

CircularBuffer::~CircularBuffer() {
    free(buffer_);
}

bool CircularBuffer::insert(float item) {
    buffer_[idx_] = item;
    idx_++;

    if (filled_ == false && idx_ == size_) {
        filled_ = true;
        idx_ = 0;

        return true;
    } else if(idx_ == size_) {
        idx_ = 0;

        return true;
    }

    return false;
}

float CircularBuffer::get(int pos) {
    if (pos < size_) {
        return buffer_[pos];
    } else {
        throw std::out_of_range("The position is higher than the size (out of range)");
    }
}

bool CircularBuffer::isFilled() {
    return filled_;
}

void CircularBuffer::setSize(int size) {
    free(buffer_);

    size_ = size;
    buffer_ = (float *) malloc(sizeof(float)*(size_+1));

    if(buffer_ == NULL) {
        throw std::bad_alloc();
    }

    reset();
}

int CircularBuffer::getSize() {
    return size_;
}

void CircularBuffer::reset(bool fast) {
    filled_ = false;
    idx_ = 0;

    if(fast) {
        return ;
    }

    for(int i = 0; i < size_; i++) {
        buffer_[i] = 0;
    }

}
