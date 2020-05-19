#include<cstdio>
#include<cstring>


int getHash(const char* str, int str_len, int q, int d) {
    int str_hash = 0;
    for (int i = 0; i < str_len; i++) {
        str_hash = (d * str_hash + str[i]) % q;
    }

    return str_hash;
}

void search(const char* pattern, const char* data, int q, int d) {
    int pat_len = strlen(pattern);
    int h = 1;
    for (int i = 0; i < pat_len - 1; i++) {
        h = (h * d) % q;
    }

    int pat_hash = getHash(pattern, pat_len, q, d);
    int data_hash = getHash(data, pat_len, q, d);

    int data_len = strlen(data);
    for (int i = 0; i <= data_len - pat_len; i++) {
        if (pat_hash == data_hash) {
            if (memcmp(&data[i], &pattern[0], pat_len) == 0) {
                printf("Pattern found at index %d \n", i);
                
            }
        }

        data_hash = (d * (data_hash - data[i] * h) + data[i + pat_len]) % q;
        if (data_hash < 0) {
            data_hash = (data_hash + q);
        }
    }
}

const int q_value = 881;
const int d_value = 256;

int main(int argc, char** argv) {
    FILE* in_file = fopen(argv[1], "rb");

    char buf[512];
    for (;;) {
        int ch_read = fread(buf, 1, sizeof(buf), in_file);

        if (ch_read == 0) {
            break;
        }

        search(argv[2], buf, q_value, d_value);
    }

    return 0;
}