/*
 * assignment_tuner
 * Student: Bruno Luiz da Silva
 * ID: 150724708
 * RTDSP 2016
 *
 * Andrew McPherson and Victor Zappi
 * Queen Mary, University of London
 */

#include "buffer.h"
#include <cstdlib>
#include <cstdio>

#include <stdexcept>

Buffer::Buffer(int bufferSize): full_(false), idx_(0), size_(bufferSize), getIdx_(0) {
    setSize(bufferSize);
}

Buffer::~Buffer() {
    free(buffer_);
}

bool Buffer::insert(float item) {
    buffer_[idx_] = item;
    idx_++;

    if (full_ == false && idx_ == size_) {
        full_ = true;

        return false;
    }

    return true;
}

float Buffer::get(int pos) {
    if (pos < size_) {
        return buffer_[pos];
    } else {
        throw std::out_of_range("The position is higher than the size (out of range)");
    }
}

bool Buffer::isFull() {
    return full_;
}

void Buffer::setSize(int size) {
    free(buffer_);

    size_ = size;
    buffer_ = (float *) malloc(sizeof(float)*(size_+1));

    if(buffer_ == NULL) {
        throw std::bad_alloc();
    }

    reset();
}

int Buffer::getSize() {
    return size_;
}

void Buffer::reset(bool fast) {
    full_ = false;
    idx_ = 0;

    if(fast) {
        return ;
    }

    for(int i = 0; i < size_; i++) {
        buffer_[i] = 0;
    }

}
