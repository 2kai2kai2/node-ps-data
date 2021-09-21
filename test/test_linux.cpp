#include "../lib_linux.cc"
#include <iostream>

int main() {
    std::cout << cpuTimeCpp(1) << std::endl;
    std::cout << memInfoCpp(1) << std::endl;
}