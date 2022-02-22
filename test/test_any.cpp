#include "../lib.h"
#include <iostream>

int main() {
    size_t pid;
    std::cout << "Enter PID: ";
    std::cin >> pid;

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

    std::cout << " == FILE IO == " << std::endl;
    size_t readSize, readCount, writeSize, writeCount;
    fileInfoCpp(pid, readSize, readCount, writeSize, writeCount);
    std::cout << "Read: " << readSize << " bytes in " << readCount << " operations" << std::endl;
    std::cout << "Write: " << writeSize << " bytes in " << writeCount << " operations" << std::endl;
}