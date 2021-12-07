#include "lib.h"
#include <iostream>
#include <libproc.h>

/**
Gets the CPU time used by a process in milliseconds.
 */
bool cpuTimeCpp(const size_t& pid, size_t& user, size_t& kernel) {
    proc_taskinfo info;
    int ret = proc_pidinfo(pid, PROC_PIDTASKINFO, 0, (void*)&info,
                           PROC_PIDTASKINFO_SIZE);
    if (ret > 0) {
        // Success!
        user = info.pti_total_user / 1000000;
        kernel = info.pti_total_system / 1000000;
        return true;
    } else {
        std::cerr << "Failed to get data about process " << pid
                  << " while trying to access cpu data." << std::endl;
        return false;
    }
    return true;
}

/**
Gets memory info in bytes.
*/
bool memInfoCpp(const size_t& pid, size_t& total, size_t& workingSet) {
    proc_taskinfo info;
    int ret = proc_pidinfo(pid, PROC_PIDTASKINFO, 0, (void*)&info,
                           PROC_PIDTASKINFO_SIZE);
    if (ret > 0) {
        // Success!
        total = info.pti_resident_size + info.pti_virtual_size;
        workingSet = info.pti_resident_size;
        return true;
    } else {
        std::cerr << "Failed to get data about process " << pid
                  << " while trying to access memory data." << std::endl;
        return false;
    }
    return true;
}