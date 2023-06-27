/**
 * @file lib_mac.cc
 * @author @2kai2kai2
 * 
 * @copyright Copyright (c) 2023 Kai Orita
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include "lib.h"
#include <iostream>
#include <libproc.h>

/**
 * Gets the CPU time used by a process in milliseconds.
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
 * Gets memory info in bytes.
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

/**
 * Gets file IO information
 * NOTE: MacOS version currently returns number of read/write operations as 0.
 */
bool fileInfoCpp(const size_t& pid, size_t& readSize, size_t& readCount,
                 size_t& writeSize, size_t& writeCount) {
    rusage_info_current info;
    if (proc_pid_rusage(pid, RUSAGE_INFO_CURRENT, (rusage_info_t*)&info)) {
        std::cerr << "Failed to get data about process " << pid
                  << " while trying to access file IO data." << std::endl;
        return false;
    }
    // Success!
    readSize = info.ri_diskio_bytesread;
    writeSize = info.ri_diskio_byteswritten;
    readCount = writeCount = 0;
    return true;
}