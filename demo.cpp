#include <ctime>
#include <iostream>

#include "galois_field.h"
#include "rs_fec.h"

int main(int argc, char **argv) {
    int n = 10;
    int m = 7;
    int size = 30;
    int loss = 5;
    srand(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch())
              .count());

    uint8_t **data = new uint8_t *[n];
    for (int i = 0; i < n; ++i) {
        data[i] = new uint8_t[size];
        for (int j = 0; j < size; ++j) data[i][j] = 'A' + (rand() % ('Z' - 'A'));
        data[i][size - 1] = '\0';
    }

    uint8_t **redundance_data;
    int ret = poca::rs_fec_encode(&redundance_data, data, size, n, m);

    std::cout << "Source data:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << data[i] << std::endl;
    }
    std::cout << std::endl;

    for (int i = 0; i < n; ++i) {
        int k = rand() % (n - i);
        if (k < loss) {
            data[i] = nullptr;
            --loss;
            std::cout << "Loss: " << i << std::endl;
        }
    }
    // data[0] = data[3] = data[5] = data[6] = data[8] = nullptr;
    std::cout << std::endl;

    uint8_t **src_data = new uint8_t *[n + m];
    for (int i = 0; i < n; ++i) src_data[i] = data[i];
    for (int i = 0; i < m; ++i) src_data[n + i] = redundance_data[i];
    uint8_t **recover_data;
    ret = poca::rs_fec_decode(&recover_data, src_data, size, n, m);

    std::cout << "Recovered data:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << recover_data[i] << std::endl;
    }
    std::cout << std::endl;

    return 0;
}