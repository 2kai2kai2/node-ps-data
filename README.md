# node-ps-data

[
![GitHub version](https://img.shields.io/github/package-json/v/2kai2kai2/node-ps-data?logo=Github)
](https://github.com/2kai2kai2/node-ps-data/releases/latest)
[
![Build Release](https://img.shields.io/github/actions/workflow/status/2kai2kai2/node-ps-data/npm-publish.yml?logo=GitHub)
](https://github.com/2kai2kai2/node-ps-data/actions/workflows/npm-publish.yml)
[
![NPM version](https://img.shields.io/npm/v/node-ps-data?logo=npm)
![NPM downloads](https://img.shields.io/npm/dt/node-ps-data?logo=npm)
](https://www.npmjs.com/package/node-ps-data)
[
![License GPL-3.0](https://img.shields.io/github/license/2kai2kai2/node-ps-data)
](https://github.com/2kai2kai2/node-ps-data/blob/main/LICENSE)

## Get data about process resources without executing terminal commands

- That's right. Unlike existing tools, this module directly retrieves data about processes without needing to open a new shell and wait for a terminal command's response.
- Supports Windows, Linux, and MacOS
- NodeJS module written in C++
- Prebuilt binaries for `linux-x64`, `win32-x64`, `darwin-x64`, and `darwin-arm64` (Darwin is the MacOS kernel)

## Features

- `cpuUserTime(pid)`: Get user-mode CPU usage for a process in milliseconds.
- `cpuKernelTime(pid)`: Get kernel/system-mode CPU usage for a process in milliseconds.
- `cpuTime(pid)`: Get total CPU usage for a process in milliseconds (equivalent to `cpuUserTime(pid) + cpuKernelTime(pid)`).
- `memInfo(pid)`: Get current memory usage for a process in bytes.
- `fileRead(pid)`: Get total file read size for a process in bytes.
- `fileWrite(pid)`: Get total file write size for a process in bytes.

## Installation

```
npm install node-ps-data
```

----

## Known Issues and Future Plans

- Build more binaries for other platforms and architectures.
- More library functions:
	- CPU/Memory subcategories (e.g. child process time, pages info, etc.)
	- Network usage
	- More!

## License & Copyright
Copyright (c) 2023 Kai Orita

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
 