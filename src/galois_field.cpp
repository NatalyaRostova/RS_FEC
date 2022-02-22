#include "galois_field.h"

#include <iostream>
#include <mutex>
#include <thread>

namespace rs_fec_poca {

    int16_t **multi_table;
    int16_t **div_table;
    int16_t *log_table;
    int16_t *exp_table;

    void init_galois_field_1() {
        int bits = 8;
        int size = 1 << bits;
        log_table = new int16_t[size];
        exp_table = new int16_t[size];
        typedef int16_t *int16_ptr;
        multi_table = new int16_ptr[size];
        div_table = new int16_ptr[size];
        for (int i = 0; i < size; ++i) {
            multi_table[i] = new int16_t[size];
            div_table[i] = new int16_t[size];
        }

        exp_table[0] = 1;
        exp_table[size - 1] = 0;
        log_table[0] = 255;
        log_table[1] = 0;

        for (int i = 1; i < size - 1; ++i) {
            exp_table[i] = exp_table[i - 1] << 1;

            //最高指数已经到了8，需要模上m(x)
            if (exp_table[i] & 0x100) {
                exp_table[i] ^= 0x11D;
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
                div_table[i][j] = exp_table[(size - 1 + log_table[i] - log_table[j]) % (size - 1)];
            }
        }
#if LOG_PRINT_DIV_TABLE
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << div_table[i][j] << " ";
            }
            std::cout << std::endl;
        }
#endif

#if LOG_PRINT_MULTI_TABLE
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << div_table[i][j] << " ";
            }
            std::cout << std::endl;
        }
#endif

#if LOG_PRINT_EXP_TABLE
        for (int i = 0; i < size; ++i) {
            std::cout << exp_table[i] << " ";
        }
        std::cout << std::endl;
#endif

#if LOG_PRINT_LOG_TABLE
        for (int i = 0; i < size; ++i) {
            std::cout << log_table[i] << " ";
        }
        std::cout << std::endl;
#endif
    }

    std::mutex init_mux;
    bool init_flag = false;

    void gf2_8::init_galois_field() {
        init_mux.lock();
        if (!init_flag) {
            init_galois_field_1();
            init_flag = true;
        }
        init_mux.unlock();
    }

    gf2_8::gf2_8() { val_ = 0; }
    gf2_8::gf2_8(uint8_t val) { val_ = val; }
    gf2_8::~gf2_8() {}
}  // namespace rs_fec_poca