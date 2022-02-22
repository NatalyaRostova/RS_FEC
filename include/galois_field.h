#ifndef GALOIS_FIELD_H_443NIN798NUI39N
#define GALOIS_FIELD_H_443NIN798NUI39N

#include <mutex>
#include <vector>

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
