const addon = require("node-gyp-build")(__dirname);

/**
 * @param pid Process ID to search for.
 * @returns Process user-mode CPU usage time in ms.
 */
export function cpuUserTime(pid: number): number {
    return addon.cpuUserTime(pid);
}

/**
 * @param pid Process ID to search for.
 * @returns Process kernel-mode (system-mode) CPU usage time in ms.
 */
export function cpuKernelTime(pid: number): number {
    return addon.cpuKernelTime(pid);
}

/**
 * @param pid Process ID to search for.
 * @returns Process total CPU usage time in ms.
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