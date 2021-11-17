"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.memInfo = exports.cpuTime = exports.cpuKernelTime = exports.cpuUserTime = void 0;
var addon = require("node-gyp-build")(__dirname);
/**
 * @param pid Process ID to search for.
 * @returns Process user-mode CPU usage time in ms.
 */
function cpuUserTime(pid) {
    return addon.cpuUserTime(pid);
}
exports.cpuUserTime = cpuUserTime;
/**
 * @param pid Process ID to search for.
 * @returns Process kernel-mode (system-mode) CPU usage time in ms.
 */
function cpuKernelTime(pid) {
    return addon.cpuKernelTime(pid);
}
exports.cpuKernelTime = cpuKernelTime;
/**
 * @param pid Process ID to search for.
 * @returns Process total CPU usage time in ms.
 */
function cpuTime(pid) {
    return addon.cpuTime(pid);
}
exports.cpuTime = cpuTime;
/**
 * @param pid Process ID to search for.
 * @returns Memory usage in kb. Windows includes shared working set while linux is more strict.
 */
function memInfo(pid) {
    return addon.memInfo(pid);
}
exports.memInfo = memInfo;
