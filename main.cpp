#include <ctime>
#include <iostream>

#include "galois_field.h"
#include "rs_fec.h"

int main(int argc, char **argv) {
    int n = 10;
    int m = 5;
    int size = 10;
    int loss = 3;
    srand((unsigned)time(nullptr));

    uint8_t **data = new uint8_t *[n];
    for (int i = 0; i < n; ++i) {
        data[i] = new uint8_t[size];
        for (int j = 0; j < size; ++j) data[i][j] = rand() % 255;
    }

    uint8_t **redundance_data;
    int ret = poca::rs_fec_encode(&redundance_data, data, size, n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < size; ++j) std::cout << (int)data[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < size; ++j) std::cout << (int)redundance_data[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    data[1] = data[3] = data[9] = nullptr;

    uint8_t **src_data = new uint8_t *[n + m];
    for (int i = 0; i < n; ++i) src_data[i] = data[i];
    for (int i = 0; i < m; ++i) src_data[n + i] = redundance_data[i];
    uint8_t **recover_data;
    ret = poca::rs_fec_recov(&recover_data, src_data, size, n, m);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < size; ++j) std::cout << (int)recover_data[i][j] << " ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    return 0;
}