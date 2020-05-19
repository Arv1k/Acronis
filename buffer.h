#ifndef ACRONIS_BUFFER_H
#define ACRONIS_BUFFER_H


class buffer {
private:
    char* data_;
    int   capacity_;
    int   size_;

public:
    explicit buffer(int capacity): capacity_(capacity), size_(0) {
        data_ = new char[capacity_];
    }

    ~buffer() {
        delete [] data_;
        capacity_ = -1;
        size_     = -1;
    }

    char* data() {
        return data_;
    }

    int capacity() {
        return capacity_;
    }

    int size() {
        return size_;
    }

    void change_size(int new_size) {
        size_ = new_size;
    }
};


#endif //ACRONIS_BUFFER_H
