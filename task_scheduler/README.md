# C Cooperative Task Scheduler

A lightweight, round-robin cooperative task scheduler written in C. This project demonstrates how to use POSIX timers (`setitimer`) and signal handling to execute multiple functions at varying intervals on a single thread.

## Features

- **Time-Triggered Execution:** Schedules tasks to run at defined intervals using `SIGALRM`.

- **Resource Efficient:** Utilizes `pause()` to suspend CPU execution between ticks, reducing CPU usage to nearly 0%.

- **Interrupt-Safe:** Prevents deadlocks by keeping non-async-signal-safe functions (like `printf`) out of the Interrupt Service Routine (ISR) via `volatile sig_atomic_t` flags.

- **Graceful Shutdown:** Intercepts `Ctrl+C` (`SIGINT`) to safely exit the main loop and perform cleanup before termination.

- **Visual Feedback:** Uses ANSI escape codes for colored terminal output to easily distinguish between running tasks.

- **Modular Architecture:** Cleanly separates definitions and prototypes (`header.h`) from implementation logic (`main.c`).

## File Structure

- `header.h` - Contains includes, macro definitions (ANSI colors), data structures (`TskSchedulerStruct`), enums, and function prototypes.

- `main.c` - Contains the timer setup, signal handlers, main execution loop, and the simulated tasks.

## Prerequisites

This scheduler relies on POSIX standards (`<sys/time.h>`, `<signal.h>`, `<unistd.h>`). It is designed to be compiled and run on Linux, macOS, or any POSIX-compliant environment.

## Compilation & Execution

1. Clone the repository or download the source files.

2. Open your terminal in the project directory.

3. Compile the code using GCC:

```bash

gcc main.c -o scheduler

```

4. Run the executable:

```bash

./scheduler


```

## Expected Output

Upon running, you will see a startup banner, followed by colored task executions based on their defined intervals (e.g., Task A every 1 sec, Task B every 2 secs, Task C every 4 secs).

```
=================================================

Task scheduler started. Press [Ctrl+C] to exit.

=================================================



This is Task A for tick=1

This is Task B for tick=1

This is Task A for tick=2

This is Task A for tick=3

This is Task B for tick=3

This is Task A for tick=4

This is Task C for tick=4

^C

Scheduler shutting down gracefully. Final tick: 4

```

## How It Works

1. **Initialization:** The `TskSchedulerStruct` array defines which functions to run, their tick intervals, and their starting offsets.

2. **Timer Setup:** `setitimer` configures a hardware timer to send a `SIGALRM` every 1 second.

3. **Signal Handling:** The ISR simply sets a `flag` to true.

4. **Execution Loop:** The `main` loop wakes up from `pause()`, checks the flag, increments the master `tick`, and iterates through the task array to see which tasks are due for execution based on the modulo of their interval.
