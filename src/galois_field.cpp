#include "galois_field.h"

#include <mutex>

std::once_flag init_once_flag;

uint8_t **multi_table;
uint8_t **div_table;
uint8_t *log_table;
uint8_t *exp_table;

void init_galois_field_1() {
    int bits = 8;
    int size = 1 << bits;
    log_table = new uint8_t[size];
    exp_table = new uint8_t[size];
    typedef uint8_t *uint8_ptr;
    multi_table = new uint8_ptr[size];
    div_table = new uint8_ptr[size];
    for (int i = 0; i < size; ++i) {
        multi_table[i] = new uint8_t[size];
        div_table[i] = new uint8_t[size];
    }

    exp_table[0] = 1;
    exp_table[size - 1] = 0;
    log_table[0] = 255;
    log_table[1] = 0;

    for (int i = 1; i < size - 1; ++i) {
        exp_table[i] = (exp_table[i - 1] << 1) ^ exp_table[i - 1];

        //最高指数已经到了8，需要模上m(x)
        if (exp_table[i] & 0x100) {
            exp_table[i] ^= 0x11B;
        }

        log_table[exp_table[i]] = i;
    }

    multi_table[0][0] = 0;
    for (int i = 1; i < size; ++i) {
        for (int j = i + 1; j < size; ++j) {
            multi_table[i][j] = multi_table[j][i] = exp_table[(log_table[i] + log_table[j]) % (size - 1)];
        }
        multi_table[i][i] = exp_table[(log_table[i] + log_table[i]) % (size - 1)];
        multi_table[i][0] = multi_table[0][i] = 0;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 1; j < size; ++j) {
            div_table[i][j] = exp_table[(log_table[i] - log_table[j] + size - 1) % (size - 1)];
        }
    }
}

void rs_fec_poca::gf2_8::init_galois_field() { std::call_once(init_once_flag, init_galois_field_1); }