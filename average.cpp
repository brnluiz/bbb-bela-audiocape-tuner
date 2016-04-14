#include "average.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>

Average::Average(int sizeInitial, int sizeStep): size_(sizeInitial), step_(sizeStep) {
    setSize(sizeInitial);
}

Average::~Average() {
    free(data_);
}

bool Average::insert(float item) {
    // Cannot insert more data
    if (idx_ == size_) {
        increaseSize();
    }

    data_[idx_] = item;
    idx_++;

    return true;
}

void Average::setSize(int size, bool keep) {
    // Copy the actual buffer data to a temporary one
    float *tmpData;
    if (keep) {
        tmpData = (float *) malloc(sizeof(float)*(size_+1));
        memcpy(tmpData, data_, sizeof(float)*(size_+1));
    }

    free(data_);

    // Resize/malloc the dataset
    size_ = size;
    data_ = (float *) malloc(sizeof(float)*(size_+1));

    if(data_ == NULL) {
        printf("Out of memory!");
        exit(1);
    }

    // Recopy the previous data to the new dataset or reset it
    if (keep) {
        memcpy(data_, tmpData, sizeof(float)*(size_+1));
        free(tmpData);
    } else {
        reset();
    }
}

int Average::getSize() {
    return idx_;
}

int Average::getPossibleSize() {
    return size_;
}

float Average::get(int pos) {
    if (pos < size_) {
        return data_[pos];
    } else {
        return -1;
    }
}

void Average::reset(bool fast) {
    idx_ = 0;

    if(fast) {
        return ;
    }

    for(int i = 0; i < size_; i++) {
        data_[i] = 0;
    }
}

void Average::increaseSize(int step)
{
    if (step == 0) {
        step = step_;
    }

    int newSize = step + size_;
    setSize(newSize, true);
}

float Average::arithmetic() {
    float sum = 0;
    float avg = 0;

    for (int i = 0; i < idx_; i++) {
        sum += data_[i];
    }

    avg = sum/idx_;

    return avg;
}
