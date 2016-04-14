#include "cyclicbuffer.h"
#include <cstdlib>
#include <cstdio>

CyclicBuffer::CyclicBuffer(int bufferSize): filled_(false), idx_(0), size_(bufferSize) {
    setSize(bufferSize);
}

CyclicBuffer::~CyclicBuffer() {
    free(buffer_);
}

bool CyclicBuffer::insert(float item) {
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

float CyclicBuffer::get(int pos) {
    if (pos < size_) {
        return buffer_[pos];
    } else {
        return -1;
    }
}

bool CyclicBuffer::isFilled() {
    return filled_;
}

void CyclicBuffer::setSize(int size) {
    free(buffer_);

    size_ = size;
    buffer_ = (float *) malloc(sizeof(float)*(size_+1));

    if(buffer_ == NULL) {
        printf("Out of memory!");
        exit(1);
    }

    reset();
}

int CyclicBuffer::getSize() {
    return size_;
}

void CyclicBuffer::reset(bool fast) {
    filled_ = false;
    idx_ = 0;

    if(fast) {
        return ;
    }

    for(int i = 0; i < size_; i++) {
        buffer_[i] = 0;
    }

}
