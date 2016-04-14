#ifndef AVERAGE_H
#define AVERAGE_H

class Average
{
public:
    Average(int sizeInitial = 5, int sizeStep = 10);
    ~Average();

    float arithmetic();

    bool insert(float item);
    float get(int pos);

    void setSize(int size, bool keep = false);
    int  getSize();
    int  getPossibleSize();

    void reset(bool fast = false);
private:
    void increaseSize(int step = 0);
    int idx_;
    float *data_;
    int size_;
    int step_;
};

#endif // AVERAGE_H
