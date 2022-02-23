#include "rs_fec_encode.h"

#include <vector>

namespace rs_fec_poca {
    gf2_8 **init_encode_matrix(int n, int m) {
        gf2_8 **ret = new gf2_8 *[n + m];
        for (int i = 0; i < m + n; ++i) {
            ret[i] = new gf2_8[n];
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) ret[i][j] = 0;
            ret[i][i] = 1;
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) ret[n + i][j] = gf_2_8_power(i + 1, j);
        }
        return ret;
    }
    int rs_fec_encode(uint8_t **dst, int *dst_linesize, uint8_t **src, int *src_linesize, int n, int m) {
        init_galois_field();
        gf2_8 **matrix = init_encode_matrix(n, m);
        return 0;
    }

}  // namespace rs_fec_poca