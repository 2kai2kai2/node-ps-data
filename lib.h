#pragma once
#include <cstddef>

bool cpuTimeCpp(const size_t& pid, size_t& user, size_t& kernel);

bool memInfoCpp(const size_t& pid, size_t& total, size_t& workingSet);

bool fileInfoCpp(const size_t& pid, size_t& readSize, size_t& readCount,
                 size_t& writeSize, size_t& writeCount);