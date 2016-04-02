#include "cyclicbuffer.h"
#include <cstdlib>
#include <cstdio>

CyclicBuffer::CyclicBuffer(int bufferSize): filled_(false), idx_(0), bufferSize_(bufferSize) {
    buffer_ = (float *) malloc(sizeof(float)*(bufferSize_+1));
    if(buffer_ == NULL) {
        printf("Out of memory!");
        exit(1);
    }

    for(int i = 0; i < bufferSize_; i++) {
        buffer_[i] = 0;
    }
}

CyclicBuffer::~CyclicBuffer() {
    free(buffer_);
}

bool CyclicBuffer::insert(float item) {
    buffer_[idx_] = item;
    idx_++;

    if (filled_ == false && idx_ == bufferSize_) {
        filled_ = true;
        idx_ = 0;

        return true;
    } else if(idx_ == bufferSize_) {
        idx_ = 0;

        return true;
    }

    return false;
}

float CyclicBuffer::get(int pos) {
    if (pos < bufferSize_) {
        return buffer_[pos];
    } else {
        return -1;
    }
}

bool CyclicBuffer::isFilled()
{
    return filled_;
}
