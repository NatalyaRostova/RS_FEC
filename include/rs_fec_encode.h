#ifndef RS_FEC_ENCODE_H_32NIU3232N3NJ32
#define RS_FEC_ENCODE_H_32NIU3232N3NJ32
#include "galois_field.h"

namespace rs_fec_poca {
    /**
     * 对数据进行RSFEC编码
     * @param dst 编码结果数据包矩阵, 总共应当有(n + m)个包
     * @param dst_linesize 编码结果数据包每个包的长度, dst_linesize的长度应为(n + m)
     * @param src 原始数据包矩阵, 总共应当有n个包
     * @param src_linesize 原始数据包每个包的长度, src_linesize的长度应为n
     * @param n 原始数据包的个数, 即src中有多少行
     * @param m 冗余包数量的个数
     * @return 0表示成功, < 0表示失败
     */
    int rs_fec_encode(uint8_t **dst, int *dst_linesize, uint8_t **src, int *src_linesize, int n, int m);
}  // namespace rs_fec_poca

#endif  // RS_FEC_ENCODE_H_32NIU3232N3NJ32