/**
 * @file test_mem_basic.ts
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


const proc = require('process');
const ps = require('node-ps-data');
const assert = require('assert');
const pid = proc.pid;

let count = 0;
let buffer = "";
const MAX_MEM = 1024 * 1024 * 16; // 16MB
const TRIALS = 2000;
let failures = 0;

for (let i = 0; i < 400; ++i) {
    let prev_mem = ps.memInfo(pid);
    if (typeof prev_mem !== 'number' || prev_mem < 0) {
        throw new Error('Invalid memory: ' + prev_mem);
    }
    if (i % 2 === 0) {
        let post_mem = ps.memInfo(pid);
        // increase mem (top third)
        buffer = String.fromCharCode(97 + Math.floor(26 * Math.random())).repeat(Math.ceil(MAX_MEM - Math.random() * MAX_MEM / 3));
        if (typeof post_mem !== 'number' || post_mem < buffer.length) {
            throw new Error('Invalid memory: ' + post_mem);
        }
        if (post_mem < prev_mem) {
            failures++;
        }
    } else {
        let post_mem = ps.memInfo(pid);
        // decrease mem (bottom third)
        buffer = String.fromCharCode(97 + Math.floor(26 * Math.random())).repeat(Math.floor(Math.random() * MAX_MEM / 3));
        if (typeof post_mem !== 'number' || post_mem < buffer.length) {
            throw new Error('Invalid memory: ' + post_mem);
        }
        if (post_mem > prev_mem) {
            failures++;
        }
    }
}
if (TRIALS * 0.01 < failures) {
    throw new Error('Too many failures: ' + failures + '/' + TRIALS);
} else {
    console.log('Basic memory test passed with only ' + failures + '/' + TRIALS + ' failures.');
}