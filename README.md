## Lookup data about processes without executing terminal commands
- That's right. Unlike existing tools, this module directly looks up data about processes without needing to open a new shell and wait for the response.
- Supports both Windows and Linux
- NodeJS module written in c++

## Features
- `cpuTime(pid)`: Get total CPU usage for a process in milliseconds.
- `memInfo(pid)`: Get current memory usage for a process in bytes.
