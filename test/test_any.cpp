#include "../lib.h"
#include <iostream>

int main() {
    size_t pid = 94058;

    std::cout << " == CPU == " << std::endl;
    size_t user, kernel;
    cpuTimeCpp(pid, user, kernel);
    std::cout << "User: " << user << std::endl;
    std::cout << "Kernel: " << kernel << std::endl;

    std::cout << " == MEMORY == " << std::endl;
    size_t total, rss;
    memInfoCpp(pid, total, rss);
    std::cout << "Total: " << total << std::endl;
    std::cout << "Working Set: " << rss << std::endl;
}