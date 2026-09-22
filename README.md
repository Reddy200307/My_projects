# C Systems Programming Portfolio

A collection of high-performance C projects focusing on system-level programming, memory management, and POSIX operating system interactions.

## 📁 Repository Structure

### 1. [Embedded Micro DB (uDb)](https://github.com/Reddy200307/My_projects/tree/master/Embedded_uDB)

A high-performance, in-memory database engine designed for embedded systems. Built in pure C using a tail-optimized doubly linked list architecture, it is designed to optimize memory bandwidth and handle massive datasets.

- **Scale:** Successfully handles up to 50,000,000 nodes in RAM without crashing.
- **Speed:** Achieves ultra-fast ingestion, allocating and linking approximately 50.4 million nodes per second.
- **I/O Optimization:** Features dual persistence modes, where the custom binary I/O layer performs about 10x faster than traditional CSV text storage.
- **Capabilities:** Includes complete CRUD operations, smart I/O buffering to drastically reduce disk syscalls, and a built-in "Chaos Benchmarking Suite" for stress testing.

### 2. [C Cooperative Task Scheduler](https://github.com/Reddy200307/My_projects/tree/master/task_scheduler)

A lightweight, round-robin cooperative task scheduler demonstrating the use of POSIX hardware timers and interrupt-safe signal handling on a single thread.

- **Time-Triggered Execution:** Schedules multiple functions to run at distinct intervals using `setitimer` and `SIGALRM`.
- **Resource Efficient:** Utilizes the `pause()` system call to suspend CPU execution between timer ticks, dropping idle CPU usage to near 0%.
- **Robust Signal Handling:** Safely bridges Interrupt Service Routines (ISRs) and the main loop using `volatile sig_atomic_t` flags, preventing compiler optimization errors and deadlocks.
- **Graceful Shutdown:** Intercepts `Ctrl+C` (`SIGINT`) to safely clean up and exit the main loop instead of forcefully terminating.

**Author:** Prashanth
