/**
 * @file index.ts
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
const addon = require("node-gyp-build")(__dirname);

/**
 * @param pid Process ID to search for.
 * @returns Process user-mode CPU usage time in ms, or 0 if not found.
 */
export function cpuUserTime(pid: number): number {
    return addon.cpuUserTime(pid);
}

/**
 * @param pid Process ID to search for.
 * @returns Process kernel-mode (system-mode) CPU usage time in ms, or 0 if not found.
 */
export function cpuKernelTime(pid: number): number {
    return addon.cpuKernelTime(pid);
}

/**
 * @param pid Process ID to search for.
 * @returns Process total CPU usage time in ms, or 0 if not found.
 */
export function cpuTime(pid: number): number {
    return addon.cpuTime(pid);
}

/**
 * @param pid Process ID to search for.
 * @returns Memory usage in kb. Windows includes shared working set while linux is more strict.
 */
export function memInfo(pid: number): number {
    return addon.memInfo(pid);
}

/**
 * @param pid Process ID to search for.
 * @returns Number of bytes process has read from file.
 */
export function fileRead(pid: number): number {
    return addon.fileRead(pid);
}

/**
 * @param pid Process ID to search for.
 * @returns Number of bytes process has written to file.
 */
export function fileWrite(pid: number): number {
    return addon.fileWrite(pid);
}