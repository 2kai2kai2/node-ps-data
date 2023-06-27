/**
 * @file test_any.cpp
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