#ifndef GALOIS_FIELD_H_443NIN798NUI39N
#define GALOIS_FIELD_H_443NIN798NUI39N

#include <mutex>
#include <vector>

#define LOG_PRINT_DIV_TABLE 0
#define LOG_PRINT_MULTI_TABLE 0
#define LOG_PRINT_EXP_TABLE 0
#define LOG_PRINT_LOG_TABLE 0

namespace rs_fec_poca {
    typedef uint8_t gf2_8;

    void init_galois_field();

    gf2_8 gf_2_8_add(gf2_8 num1, gf2_8 num2);
    gf2_8 gf_2_8_sub(gf2_8 num1, gf2_8 num2);
    gf2_8 gf_2_8_multi(gf2_8 num1, gf2_8 num2);
    gf2_8 gf_2_8_div(gf2_8 num1, gf2_8 num2);

    gf2_8 gf_2_8_power(gf2_8 num, uint32_t exp);

}  // namespace rs_fec_poca

#endif  // GALOIS_FIELD_H_443NIN798NUI39N
