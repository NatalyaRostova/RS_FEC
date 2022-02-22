#ifndef GALOIS_FIELD_H_443NIN798NUI39N
#define GALOIS_FIELD_H_443NIN798NUI39N

#include <mutex>
#include <vector>

#define LOG_PRINT_DIV_TABLE 0
#define LOG_PRINT_MULTI_TABLE 0
#define LOG_PRINT_EXP_TABLE 0
#define LOG_PRINT_LOG_TABLE 0

namespace rs_fec_poca {
    class gf2_8 {
    public:
        static void init_galois_field();
        gf2_8();
        gf2_8(uint8_t val);
        ~gf2_8();
    private:
        uint8_t val_;
    };

}  // namespace rs_fec_poca

#endif  // GALOIS_FIELD_H_443NIN798NUI39N
