#include "lib.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <sys/time.h>
#include <unistd.h>

/**
Gets the CPU time used by a process in milliseconds.
 */
bool cpuTimeCpp(const size_t& pid, size_t& user, size_t& kernel) {
    std::ifstream file("/proc/" + std::to_string(pid) + "/stat");
    // Check that this pid is valid
    if (!file.good()) {
        return false;
    }
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
    size_t usertime;
    file >> usertime;
    usertime = usertime * 1000 / sysconf(_SC_CLK_TCK);
    // 15 - kernel time
    size_t kerneltime;
    file >> kerneltime;
    kerneltime = kerneltime * 1000 / sysconf(_SC_CLK_TCK);
#ifdef FALSE
    // 16 - awaited child user time (not sure if this is needed, but might as well grab it just in case)
    size_t childusertime;
    file >> childusertime;
    childusertime = childusertime * 1000 / sysconf(_SC_CLK_TCK);
    // 16 - awaited child kernel time
    size_t childkerneltime;
    file >> childkerneltime;
    childkerneltime = childkerneltime * 1000 / sysconf(_SC_CLK_TCK);
#endif

    user = usertime;
    kernel = kerneltime;
    return true;
}

// /proc/[pid]/stat : all the stats for ps, manual says defined in kernel source file fs/proc/array.c

/**
Memory size in bytes

Linux uses a system where all memory is considered virtual memory stored with pages, and those addresses convert to physical (RAM) or 'virtual' memory on disk.
Retrieved from /proc/[pid]/statm
 */
bool memInfoCpp(const size_t& pid, size_t& total, size_t& workingSet) {
    std::ifstream file("/proc/" + std::to_string(pid) + "/statm");
    // Check that this pid is valid
    if (!file.good()) {
        return false;
    }
    // 1 - total size
    size_t size;
    file >> size;
    // 2 - RSS (working set; approx.)
    size_t RSS;
    file >> RSS;
    // 3-6 - size of various other parts (code, shared pages, )
    for (unsigned char i = 3; i <= 6; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
    }

    file.close();

    total = size * sysconf(_SC_PAGE_SIZE);
    workingSet = RSS * sysconf(_SC_PAGE_SIZE);
    return true;
}

/**
Gets file IO information
Retrieved from /proc/[pid]/io filesystem
 */
bool fileInfoCpp(const size_t& pid, size_t& readSize, size_t& readCount,
                 size_t& writeSize, size_t& writeCount) {
    FILE* file = fopen(("/proc/" + std::to_string(pid) + "/io").data(), "r");
    if (file == NULL)
        return false;
    fscanf(file, "rchar: %*u\n");
    fscanf(file, "wchar: %*u\n");
    fscanf(file, "syscr: %lu\n", &readCount);
    fscanf(file, "syscw: %lu\n", &writeCount);
    fscanf(file, "read_bytes: %lu\n", &readSize);
    fscanf(file, "write_bytes: %lu\n", &writeSize);
    return !fclose(file);
}