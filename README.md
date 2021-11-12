![GitHub version](https://img.shields.io/github/package-json/v/2kai2kai2/node-ps-data?logo=Github)
![NPM version](https://img.shields.io/npm/v/node-ps-data?logo=npm)
![NPM downloads](https://img.shields.io/npm/dt/node-ps-data?logo=npm)
![License GPL-3.0](https://img.shields.io/github/license/2kai2kai2/node-ps-data)

## Lookup data about processes without executing terminal commands
- That's right. Unlike existing tools, this module directly looks up data about processes without needing to open a new shell and wait for the response.
- Supports both Windows and Linux
- NodeJS module written in c++

## Features
- `cpuTime(pid)`: Get total CPU usage for a process in milliseconds.
- `memInfo(pid)`: Get current memory usage for a process in bytes.
