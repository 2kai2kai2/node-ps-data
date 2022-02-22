#include "lib.h"
#include <Windows.h>
#include <iostream>
#include <psapi.h>

/**
Gets the CPU time used by a process in milliseconds.
 */
bool cpuTimeCpp(const size_t& pid, size_t& user, size_t& kernel) {
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, true, pid);
    if (process == NULL) {
        std::cerr << "Failed to open process " << pid << " with PROCESS_QUERY_LIMITED_INFORMATION when getting cpu data." << std::endl;
        return false;
    }

    // Get data
    _FILETIME creationtime, exittime, kerneltime, usertime;
    if (!GetProcessTimes(process, &creationtime, &exittime, &kerneltime, &usertime)) {
        std::cerr << GetLastError() << std::endl;
        CloseHandle(process);
        return false;
    }
    CloseHandle(process);
    // Transform data into 64-bit number
    ULARGE_INTEGER kernelli;
    kernelli.LowPart = kerneltime.dwLowDateTime;
    kernelli.HighPart = kerneltime.dwHighDateTime;
    ULARGE_INTEGER userli;
    userli.LowPart = usertime.dwLowDateTime;
    userli.HighPart = usertime.dwHighDateTime;

    kernel = kernelli.QuadPart / 10000;
    user = userli.QuadPart / 10000;
    return true;
}

/**
Gets working set size (memory) in bytes. Includes both private and shared working sets.
Note that this is different from the value in the task manager, because that excludes the shared working set.
*/
bool memInfoCpp(const size_t& pid, size_t& total, size_t& workingSet) {
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, pid);
    if (process == NULL) {
        std::cerr << "Failed to open process " << pid << " with PROCESS_QUERY_LIMITED_INFORMATION when getting memory data." << std::endl;
        return false;
    }

    PROCESS_MEMORY_COUNTERS mem;
    if (!GetProcessMemoryInfo(process, &mem, sizeof(mem))) {
        std::cerr << GetLastError() << std::endl;
        CloseHandle(process);
        return false;
    }
    CloseHandle(process);

    workingSet = mem.WorkingSetSize;
    total = mem.WorkingSetSize + mem.PagefileUsage;
    return true;
}

/**
Gets file IO information
 */
bool fileInfoCpp(const size_t& pid, size_t& readSize, size_t& readCount,
                 size_t& writeSize, size_t& writeCount) {
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, pid);
    if (process == NULL) {
        std::cerr << "Failed to open process " << pid << " with PROCESS_QUERY_LIMITED_INFORMATION when getting file IO data." << std::endl;
        return false;
    }
    IO_COUNTERS io;
    if (!GetProcessIoCounters(process, &io)) {
        std::cerr << GetLastError() << std::endl;
        CloseHandle(process);
        return false;
    }
    CloseHandle(process);

    readSize = io.ReadTransferCount;
    readCount = io.ReadOperationCount;
    writeSize = io.WriteTransferCount;
    writeCount = io.WriteOperationCount;
    // otherSize = io.OtherTransferCount;
    // otherCount = io.OtherOperationCount;
    return true;
}