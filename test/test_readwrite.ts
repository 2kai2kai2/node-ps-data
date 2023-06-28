/**
 * @file test_readwrite.ts
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


// This is the simplest test case, since fileio is relatively predictable.
// As a result, we can test both test and check with the same process.

const proc = require('process');
const fs = require('fs');
const ps = require('node-ps-data');
const assert = require('assert');
const pid = proc.pid;

const filename = 'test_readwrite.txt';


var read = ps.fileRead(pid);
assert(typeof read === 'number' && read >= 0, 'Read was invalid: ' + read);
var write = ps.fileWrite(pid);
assert(typeof read === 'number' && write >= 0, 'Write was invalid: ' + write);
console.log('Initial Read: ' + read + ', Initial Write: ' + write);

{
  fs.writeFileSync(filename, '1234'.repeat(1000), {flag: 'w'});

  let new_read = ps.fileRead(pid);
  assert(
      new_read === read,
      'new_read should be equal to read (' + read + '), but is ' + new_read);
  read = new_read;
  let new_write = ps.fileWrite(pid);
  assert(
      new_write > write,
      'new_write should be more than write (' + write + '), but is ' + new_write);
  write = new_write;
}

{
  let _ = fs.readFileSync(filename, {flag: 'r'});

  let new_read = ps.fileRead(pid);
  assert(
      new_read > read,
      'new_read should be more than read (' + read + '), but is ' + new_read);
  read = new_read;
  let new_write = ps.fileWrite(pid);
  assert(
      new_write === write,
      'new_write should be equal to write (' + write + '), but is ' + new_write);
  write = new_write;
}
