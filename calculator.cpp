#include <iostream>

#include "galois_field.h"

int main(int argc, char **argv) {
    int a, b;
    char o;
    using namespace poca;
    init_galois_field();
    std::cout << "Input q to exit\n";
    std::cout << "Compute example: \n1 + 2\n1 - 2\n1 * 2\n1 / 2\n1 ^ 2\n";
    std::cout << "Please make sure that the number you enter is between 0 and 255\n";
    while (std::cin >> a >> o >> b) {
        switch (o) {
            case '+':
                std::cout << int(gf_2_8_add(gf2_8(a), gf2_8(b))) << std::endl;
                break;
            case '-':
                std::cout << int(gf_2_8_sub(gf2_8(a), gf2_8(b))) << std::endl;
                break;
            case '*':
                std::cout << int(gf_2_8_multi(gf2_8(a), gf2_8(b))) << std::endl;
                break;
            case '/':
                std::cout << int(gf_2_8_div(gf2_8(a), gf2_8(b))) << std::endl;
                break;
            case '^':
                std::cout << int(gf_2_8_power(gf2_8(a), gf2_8(b))) << std::endl;
                break;
            case 'q':
                goto finish;
            default:
                break;
        }
    }
finish:
    return 0;
}