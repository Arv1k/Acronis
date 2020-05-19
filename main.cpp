#include <cstdio>
#include <cstring>
#include "buffer.h"


const int q_value = 881;
const int d_value = 256;

const int seq_len = 5;
const int buf_size = 512;

const int pat_len = 10;


void search(buffer* pattern, buffer* data);

int getHash(buffer* data, int length);

int main(int argc, char** argv) {
    FILE* file_in_storage = fopen(argv[1], "rb");
    FILE* some_kind_file = fopen(argv[2], "rb");

    buffer buf_storage(buf_size);
    buffer buf_some_kind(buf_size);

    for (;;) {
        int ch_read_storage =
        fread(buf_storage.data(), 1, buf_storage.capacity(), file_in_storage);
        buf_storage.change_size(ch_read_storage);

        int ch_read_some_kind =
        fread(buf_some_kind.data(), 1, buf_some_kind.capacity(), some_kind_file);
        buf_some_kind.change_size(ch_read_some_kind);

        if (ch_read_storage == 0) {
            break;
        }



        search(&buf_some_kind, &buf_storage);
    }

    return 0;
}

void search(buffer* pattern, buffer* data) {
    int h = 1;
    for (int i = 0; i < pat_len - 1; i++) {
        h = (h*d_value) % q_value;
    }

    int pat_hash = getHash(pattern, pat_len);
    int data_hash = getHash(data, pat_len);

    //for (int j = 0; j < pat_len - len; j++) {


        for (int i = 0; i <= data->size() - pat_len; i++) {
            if (pat_hash == data_hash) {
                if (memcmp(&data->data()[i], &pattern->data()[0], pat_len) == 0) {
                    printf("Pattern found at index %d \n", i);

                }
            }

            data_hash = (d_value*(data_hash - data->data()[i]*h) +
                        data->data()[i + pat_len]) % q_value;

            if (data_hash < 0) {
                data_hash += q_value;
            }
        }
    //}
}

int getHash(buffer* data, int length) {
    int data_hash = 0;
    for (int i = 0; i < length; i++) {
        data_hash = (d_value*data_hash + data->data()[i]) % q_value;
    }

    return data_hash;
}