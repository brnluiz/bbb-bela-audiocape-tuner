#ifndef CYCLICBUFFER_H
#define CYCLICBUFFER_H

class CyclicBuffer {
public:
    CyclicBuffer(int bufferSize);
    ~CyclicBuffer();

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
