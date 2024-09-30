# FreeRTOS Semaphore Example

This project demonstrates how to use a binary semaphore in FreeRTOS to synchronize two tasks (`task1` and `task2`). The tasks share a common variable `sharedValue` and perform mathematical operations on it while ensuring that the access is mutually exclusive using a semaphore.

## Description

In this example:
- `task1` increments the shared value by 5 every 2 seconds.
- `task2` decrements the shared value by 3 every 4 seconds.
- Both tasks use a binary semaphore to ensure that they do not access the shared variable simultaneously.

The semaphore guarantees that only one task can modify the `sharedValue` at a time, thus avoiding race conditions and data corruption.

## How It Works

1. **Semaphore Initialization:**
   - A binary semaphore is created using `xSemaphoreCreateBinary()`.
   - The semaphore is initialized (set to "available") by calling `xSemaphoreGive()` before starting the tasks.

2. **Task Behavior:**
   - `task1`: Tries to take the semaphore every 2 seconds. If successful, it increments the shared value by 5, prints it, and releases the semaphore.
   - `task2`: Tries to take the semaphore every 4 seconds. If successful, it decrements the shared value by 3, prints it, and releases the semaphore.

3. **Failure to Acquire Semaphore:**
   - If a task fails to acquire the semaphore within 10 ticks, it prints an error message (`Failed to take semaphore`).

## Code Breakdown

- **app_main():** Initializes the semaphore and creates both tasks.
- **task1 and task2:** These functions are run as separate tasks and perform operations on the shared variable.

## Prerequisites

- ESP-IDF installed on your machine.
- A supported ESP32 board.

## How to Run

1. Clone this repository and navigate to the project folder.
2. Run the following commands to configure and flash the code to your ESP32:
   ```bash
   idf.py set-target esp32
   idf.py menuconfig
   idf.py flash monitor
