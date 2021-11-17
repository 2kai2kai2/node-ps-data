#include "../lib_win.cc"
#include <iostream>

int main() {
    size_t user, kernel;
    cpuTimeCpp(16060, user, kernel);
    std::cout << user << std::endl;
    std::cout << kernel << std::endl;
    size_t total, rss;
    memInfoCpp(16060, total, rss);
    std::cout << total << std::endl;
    std::cout << rss << std::endl;
}