# node-ps-data

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
- `memRSS(pid)`: Get current memory resident/working set size for a process in bytes.
- `fileRead(pid)`: Get total file read size for a process in bytes.
- `fileWrite(pid)`: Get total file write size for a process in bytes.
- `NvidiaGPU.allGPUs()`: Get handles for all Nvidia GPUs (total, not process-specific data)

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
	- Process-specific GPU memory and usage
	- More!
