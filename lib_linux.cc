#include <fstream>
#include <unistd.h>
#include <sys/time.h>
#include <iostream>
#include <limits>
#include "lib.h"

/**
Gets the CPU time used by a process in milliseconds.
 */
bool cpuTimeCpp(const size_t& pid, size_t& user, size_t& kernel) {
    std::ifstream file("/proc/" + std::to_string(pid) + "/stat");
    // Check that this pid is valid
    if (!file.good()) {
        return false;
    }
    std::string temp;
    // 1 - pid
    file.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    // 2 - command, may contains spaces? surrounded by () with max length 16
    file.ignore(std::numeric_limits<std::streamsize>::max(), ')');
    file.ignore(); // skip the following space
    // 3-13 - all numbers or single characters
    for (unsigned char i = 3; i <= 13; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }
    // 14 - user time
    std::getline(file, temp, ' ');
    size_t usertime = std::stoull(temp) * 1000 / sysconf(_SC_CLK_TCK);
    // 15 - kernel time
    std::getline(file, temp, ' ');
    size_t kerneltime = std::stoull(temp) * 1000 / sysconf(_SC_CLK_TCK);
    // 16 - awaited child user time (not sure if this is needed, but might as well grab it just in case)
    std::getline(file, temp, ' ');
    size_t childusertime = std::stoull(temp) * 1000 / sysconf(_SC_CLK_TCK);
    // 16 - awaited child kernel time
    std::getline(file, temp, ' ');
    size_t childkerneltime = std::stoull(temp) * 1000 / sysconf(_SC_CLK_TCK);
    user = usertime;
    kernel = kerneltime;
    return true;
}

// /proc/[pid]/io : file io stats
// /proc/[pid]/stat : all the stats for ps, manual says defined in kernel source file fs/proc/array.c

/**
Memory size in bytes

Linux uses a system where all memory is considered virtual memory stored with pages, and those addresses convert to physical (RAM) or 'virtual' memory on disk.
Retrieved from /proc/[pid]/statm
 */
size_t memInfoCpp(const size_t& pid) {
    std::ifstream file("/proc/" + std::to_string(pid) + "/statm");
    // Check that this pid is valid
    if (!file.good()) {
        return 0;
    }
    std::string temp;
    // 1-5 - size of various other parts (code, shared pages, )
    for (unsigned char i = 1; i <= 5; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }
    // 6 - data size
    size_t pages;
    file >> pages;
    
    file.close();
    return pages * sysconf(_SC_PAGE_SIZE);
}