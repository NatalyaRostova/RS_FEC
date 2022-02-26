#include "galois_field.h"

#include <iostream>
#include <mutex>
#include <thread>

#define BITS 8
#define F_SIZE 0x100
#define F_MAX 0xFF

namespace poca {

    int16_t **multi_table;
    int16_t **div_table;
    int16_t *log_table;
    int16_t *exp_table;

    void init_galois_field_1() {
        log_table = new int16_t[F_SIZE];
        exp_table = new int16_t[F_SIZE];
        multi_table = new int16_t *[F_SIZE];
        div_table = new int16_t *[F_SIZE];
        for (int i = 0; i < F_SIZE; ++i) {
            multi_table[i] = new int16_t[F_SIZE];
            div_table[i] = new int16_t[F_SIZE];
        }

        exp_table[0] = 1;
        exp_table[F_MAX] = 0;
        log_table[0] = 255;
        log_table[1] = 0;

        for (int i = 1; i < F_MAX; ++i) {
            exp_table[i] = exp_table[i - 1] << 1;

            //最高指数已经到了8，需要模上m(x)
            if (exp_table[i] & 0x100) {
                exp_table[i] ^= 0x11D;
            }

            log_table[exp_table[i]] = i;
        }

        multi_table[0][0] = 0;
        for (int i = 1; i < F_SIZE; ++i) {
            for (int j = i + 1; j < F_SIZE; ++j) {
                multi_table[i][j] = multi_table[j][i] = exp_table[(log_table[i] + log_table[j]) % F_MAX];
            }
            multi_table[i][i] = exp_table[(log_table[i] << 1) % F_MAX];
            multi_table[i][0] = multi_table[0][i] = 0;
        }
        for (int j = 1; j < F_SIZE; ++j) {
            div_table[0][j] = 0;
        }
        for (int i = 1; i < F_SIZE; ++i) {
            for (int j = 1; j < F_SIZE; ++j) {
                div_table[i][j] = exp_table[(F_MAX + log_table[i] - log_table[j]) % F_MAX];
            }
        }
#if LOG_PRINT_DIV_TABLE
        std::cout << "Div table: " << std::endl;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << div_table[i][j] << " ";
            }
            std::cout << std::endl;
        }
#endif

#if LOG_PRINT_MULTI_TABLE
        std::cout << "Multi table: " << std::endl;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                std::cout << div_table[i][j] << " ";
            }
            std::cout << std::endl;
        }
#endif

#if LOG_PRINT_EXP_TABLE
        std::cout << "Exp table: " << std::endl;
        for (int i = 0; i < size; ++i) {
            std::cout << exp_table[i] << " ";
        }
        std::cout << std::endl;
#endif

#if LOG_PRINT_LOG_TABLE
        std::cout << "Log table: " << std::endl;
        for (int i = 0; i < size; ++i) {
            std::cout << log_table[i] << " ";
        }
        std::cout << std::endl;
#endif
    }

    std::mutex init_mux;
    bool init_flag = false;

    void init_galois_field() {
        init_mux.lock();
        if (!init_flag) {
            init_galois_field_1();
            init_flag = true;
        }
        init_mux.unlock();
    }

    gf2_8 gf_2_8_add(gf2_8 num1, gf2_8 num2) { return gf2_8(num1 ^ num2); }
    gf2_8 gf_2_8_sub(gf2_8 num1, gf2_8 num2) { return gf2_8(num1 ^ num2); }
    gf2_8 gf_2_8_multi(gf2_8 num1, gf2_8 num2) { return gf2_8(multi_table[num1][num2]); }
    gf2_8 gf_2_8_div(gf2_8 num1, gf2_8 num2) { return gf2_8(div_table[num1][num2]); }

    gf2_8 gf_2_8_power(gf2_8 num, uint32_t exp) { return gf2_8(exp_table[(log_table[num] * exp) % F_MAX]); }

}  // namespace poca