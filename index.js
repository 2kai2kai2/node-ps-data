"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
exports.memInfo = exports.cpuTime = void 0;
var addon = require("node-gyp-build")("./build/Release/node_ps_data");
/**
 * @param pid Process ID to search for.
 * @returns Process CPU usage time in ms.
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
