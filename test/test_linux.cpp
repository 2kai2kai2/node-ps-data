#include "../lib_linux.cc"
#include <iostream>

int main() {
    size_t user, kernel;
    cpuTimeCpp(1, user, kernel);
    std::cout << user << std::endl;
    std::cout << kernel << std::endl;
    size_t total, rss;
    memInfoCpp(1, total, rss);
    std::cout << total << std::endl;
    std::cout << rss << std::endl;
}