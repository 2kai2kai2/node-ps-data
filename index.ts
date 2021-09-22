const addon = require("node-gyp-build")(__dirname);

/**
 * @param pid Process ID to search for.
 * @returns Process CPU usage time in ms.
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