#ifndef BUFFER_H
#define BUFFER_H

class Buffer {
public:
    Buffer(int bufferSize);
    ~Buffer();

    virtual bool insert(float item);

    float get(int pos);

    bool isFull();

    void setSize(int size);
    int  getSize();

    void reset(bool fast = false);
protected:
    bool full_;
    int idx_;
    int getIdx_;
    float *buffer_;
    int size_;
};

#endif // BUFFER_H
