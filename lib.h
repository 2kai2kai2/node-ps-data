#pragma once
#include <cstddef>

bool cpuTimeCpp(const size_t& pid, size_t& user, size_t& kernel);

bool memInfoCpp(const size_t& pid, size_t& total, size_t& workingSet);