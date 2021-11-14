# node-ps-data

[
![GitHub version](https://img.shields.io/github/package-json/v/2kai2kai2/node-ps-data?logo=Github)
](https://github.com/2kai2kai2/node-ps-data/releases/latest)
[
![Build Release](https://img.shields.io/github/workflow/status/2kai2kai2/node-ps-data/Node.js%20Package?logo=GitHub)
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
- Supports both Windows and Linux
- NodeJS module written in C++
- Prebuilt binaries for `linux-x64` and `win32-x64`

## Features
- `cpuTime(pid)`: Get total CPU usage for a process in milliseconds.
- `memInfo(pid)`: Get current memory usage for a process in bytes.

## Installation
```
npm install node-ps-data
```

----

## Known Issues and Future Plans
- MacOS implementation.
- Build more binaries for other platforms and architectures.
- More library functions:
	- CPU/Memory subcategories (e.g. user time, kernel time, etc.)
	- Disk usage
	- Network usage
	- More!