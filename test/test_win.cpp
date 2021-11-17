#include "../lib_win.cc"
#include <iostream>

int main() {
    size_t user, kernel;
    cpuTimeCpp(1, user, kernel);
    std::cout << user << std::endl;
    std::cout << kernel << std::endl;
    std::cout << memInfoCpp(1) << std::endl;
}