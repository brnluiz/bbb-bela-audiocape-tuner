#ifndef CYCLICBUFFER_H
#define CYCLICBUFFER_H

class CyclicBuffer {
public:
    CyclicBuffer(int bufferSize);
    ~CyclicBuffer();

    bool insert(float item);
    float get(int pos);
    bool isFilled();
protected:
    bool filled_;
    int idx_;
    float *buffer_;
    int bufferSize_;
};

#endif // CYCLICBUFFER_H
