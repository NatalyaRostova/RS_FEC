#include <iostream>

#include "galois_field.h"

int main(int argc, char **argv) {
    int o, a, b;
    using namespace poca;
    init_galois_field();
    std::cout << "0: +\n1: -\n2: x\n3: /" << std::endl;
    while (std::cin >> o >> a >> b) {
        switch (o) {
            case 0:
                std::cout << int(gf_2_8_add(gf2_8(a), gf2_8(b))) << std::endl;
                break;
            case 1:
                std::cout << int(gf_2_8_sub(gf2_8(a), gf2_8(b))) << std::endl;
                break;
            case 2:
                std::cout << int(gf_2_8_multi(gf2_8(a), gf2_8(b))) << std::endl;
                break;
            case 3:
                std::cout << int(gf_2_8_div(gf2_8(a), gf2_8(b))) << std::endl;
                break;
            default:
                break;
        }
    }
    return 0;
}