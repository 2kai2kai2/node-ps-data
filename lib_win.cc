#include <Windows.h>
#include <psapi.h>
#include <iostream>

/**
Gets the CPU time used by a process in milliseconds.
 */
ULONG64 cpuTimeCpp(const size_t &pid) {
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, true, pid);
    if (process == NULL) {
        std::cerr << "Failed to open process " << pid << " with PROCESS_QUERY_LIMITED_INFORMATION when getting cpu data." << std::endl;
        return 0;
    }

    // Get data
    _FILETIME creationtime, exittime, kerneltime, usertime;
    if (!GetProcessTimes(process, &creationtime, &exittime, &kerneltime, &usertime)) {
        std::cerr << GetLastError() << std::endl;
        CloseHandle(process);
        return 0;
    }
    CloseHandle(process);
    // Transform data into 64-bit number (ULONG64 which is usually unsigned long long)
    ULARGE_INTEGER kernelli;
    kernelli.LowPart = kerneltime.dwLowDateTime;
    kernelli.HighPart = kerneltime.dwHighDateTime;
    ULARGE_INTEGER userli;
    userli.LowPart = usertime.dwLowDateTime;
    userli.HighPart = usertime.dwHighDateTime;

    const ULONG64 kernelms = kernelli.QuadPart / 10000;
    const ULONG64 userms = userli.QuadPart / 10000;

    return kernelms + userms;
}

/**
Gets working set size (memory) in bytes. Includes both private and shared working sets.
Note that this is different from the value in the task manager, because that excludes the shared working set.
*/
ULONG64 memInfoCpp(const size_t &pid) {
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, false, pid);
    if (process == NULL) {
        std::cerr << "Failed to open process " << pid << " with PROCESS_QUERY_LIMITED_INFORMATION when getting memory data." << std::endl; 
        return 0;
    }
    
    PROCESS_MEMORY_COUNTERS mem;
    if (!GetProcessMemoryInfo(process, &mem, sizeof(mem))) {
        std::cerr << GetLastError() << std::endl;
        CloseHandle(process);
        return 0;
    }
    CloseHandle(process);
    return mem.WorkingSetSize;
}