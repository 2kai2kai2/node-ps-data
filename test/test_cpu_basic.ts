/**
 * @file test_cpu_basic.ts
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

var time = 0;
const TRIALS = 1000;
var failures = 0;
for (let i = 0; i < TRIALS; i++) {
    let new_time = ps.cpuTime(pid);
    if (new_time < time)
        throw Error('Time went backwards: ' + new_time + ' < ' + time);
    if (!(new_time > time))
        failures++;
    time = new_time;
    // And do some extra computation to make sure we get more time.
    let v = 1 + Math.random();
    let u = '{"a": 1}';
    for (let j = 0; j < 1000; j++) {
        v = Math.hypot(v, Math.random(), Math.random());
        let c = JSON.parse(u);
        c[String.fromCharCode(97 + Math.floor(j * v) % 26)] = v;
        u = JSON.stringify(c);
    }
}
if (TRIALS * 0.01 < failures) {
    throw new Error('Too many failures: ' + failures + '/' + TRIALS);
} else {
    console.log('Basic CPU time test passed with only ' + failures + '/' + TRIALS + ' failures.');
}