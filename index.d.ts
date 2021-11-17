/**
 * @param pid Process ID to search for.
 * @returns Process user-mode CPU usage time in ms.
 */
export declare function cpuUserTime(pid: number): number;
/**
 * @param pid Process ID to search for.
 * @returns Process kernel-mode (system-mode) CPU usage time in ms.
 */
export declare function cpuKernelTime(pid: number): number;
/**
 * @param pid Process ID to search for.
 * @returns Process total CPU usage time in ms.
 */
export declare function cpuTime(pid: number): number;
/**
 * @param pid Process ID to search for.
 * @returns Memory usage in kb. Windows includes shared working set while linux is more strict.
 */
export declare function memInfo(pid: number): number;
