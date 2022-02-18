#ifndef RS_VEC_H_443NIN798NUI39N
#define RS_VEC_H_443NIN798NUI39N

#include <mutex>
#include <vector>

namespace rs_fec_poca {
    class Vec {
    public:
        Vec();
        Vec(uint8_t *src, size_t size);
        ~Vec();

    private:
        void initTables();
        std::vector<uint8_t> data_;
    };

}  // namespace rs_fec_poca

#endif  // RS_VEC_H_443NIN798NUI39N
