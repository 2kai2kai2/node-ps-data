
/**
 * @file index.d.ts
 * @author @2kai2kai2
 *
 * @copyright Copyright (c) 2025 2kai2kai2
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

/**
 * @param pid Process ID to search for.
 * @returns Process user-mode CPU usage time in ms, or 0 if not found.
 */
declare function cpuUserTime(pid: number): number;

/**
 * @param pid Process ID to search for.
 * @returns Process kernel-mode (system-mode) CPU usage time in ms, or 0 if not found.
 */
declare function cpuKernelTime(pid: number): number;

/**
 * @param pid Process ID to search for.
 * @returns Process total CPU usage time in ms, or 0 if not found.
 */
declare function cpuTime(pid: number): number;

/**
 * @param pid Process ID to search for.
 * @returns Total usage in bytes. Windows includes shared working set while linux is more strict.
 *
 * Note that as this includes virtual memory, it will often be extremely high on MacOS.
 */
declare function memInfo(pid: number): number;

/**
 * @param pid Process ID to search for.
 * @returns Resident/working set size in bytes. Windows includes shared working set while linux is more strict.
 *
 * Depending on operating system, this may be approximate. It represents the total amount of physical memory being used,
 * which does not include any vitual memory.
 */
declare function memRSS(pid: number): number;

/**
 * @param pid Process ID to search for.
 * @returns Number of bytes process has read from file.
 */
declare function fileRead(pid: number): number;

/**
 * @param pid Process ID to search for.
 * @returns Number of bytes process has written to file.
 */
declare function fileWrite(pid: number): number;

/**
 * The return type for `NvidiaGPU::utilization` that shows utilization of computing resources.
 * 
 * NOTE: currently only contains smUtilization (which is what most people need),
 * but things like video encode/decode accelerator data is not yet implemented.
 */
declare interface NvidiaGPUUtilization {
    /**
     * The utilization of the device's Steaming Multiprocessors (SMs)
     * 
     * This includes most 3D and compute operations.
     */
    smUtilization: number
}

/**
 * A handle for getting process data from a single Nvidia GPU (internally uses [NVML](https://docs.nvidia.com/deploy/nvml-api/nvml-api-reference.html))
 */
declare class NvidiaGPU {
    /**
     * A good entrypoint, will return handles for all Nvidia GPUs on this computer.
     * 
     * If the computer does not have Nvidia GPUs (or drivers) it will be an empty array.
     * 
     * @throws
     */
    static allGPUs(): NvidiaGPU[];

    /**
     * @param deviceIdx The index of the GPU to get a handle for.
     * @param pid The process id to search for.
     * 
     * @throws An error if `deviceIdx` is invalid or if we do not have permission to access it.
     * @throws
     */
    constructor(deviceIdx: number, pid: number);

    /**
     * Returns the process's compute utilization since the last query
     * (or if the last query was a long time ago/never, since the start of the stored buffer).
     */
    utilization(): NvidiaGPUUtilization;
}
