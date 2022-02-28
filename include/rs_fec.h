#ifndef RS_FEC_H_32NIU3232N3NJ32
#define RS_FEC_H_32NIU3232N3NJ32
#include "galois_field.h"

#define LOG_PRINT_INVERSE_MATRIX 0
#define USE_CAUCHY_MATRIX 1

namespace poca {
    /**
     * 对数据进行RSFEC编码
     * @param dst 编码冗余数据包阵列, 总共应当有m个包, 每个包长度应为size
     * @param redundance 原始数据包阵列, 总共应当有n个包, 每个包长度应为size
     * @param size 原始数据包每个包的长度, 每个数据包应当长度相等
     * @param n 原始数据包的个数, 即src中有多少行
     * @param m 冗余数据包的个数, 要求m <= n 且 m <= 255
     * @return 0表示成功, < 0表示失败
     */
    int rs_fec_encode(uint8_t ***redundance, uint8_t **src, int size, int n, int m);

    /**
     * 对数据进行恢复
     * @param dst 恢复后的数据, 长度为n
     * @param src 接收到的数据包, 长度为n + m, src[i]为第i个数据包, src[i] == nullptr 视为第i个包丢失
     * @param size 原始数据包每个包的长度, 每个数据包应当长度相等
     * @param n 原始数据包的个数, 即src中有多少行
     * @param m 冗余数据包的个数
     * @return 0表示成功, < 0表示失败
     */
    int rs_fec_decode(uint8_t ***dst, uint8_t **src, int size, int n, int m);
}  // namespace poca

#endif  // RS_FEC_H_32NIU3232N3NJ32