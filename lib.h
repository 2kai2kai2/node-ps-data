#pragma once
#include <cstddef>

bool cpuTimeCpp(const size_t& pid, size_t& user, size_t& kernel);

size_t memInfoCpp(const size_t &pid);