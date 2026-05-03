# MicroTech OS
A lightweight, open-source Real-Time Operating System (RTOS) designed for microcontrollers and embedded systems.

MicroTech OS is built from the ground up to provide maximum efficiency on resource-constrained devices. It focuses on portability, preemptive multitasking, and intelligent power management.

## ✨ Key Features
- **Preemptive Multitasking**: Round-Robin scheduling algorithm for seamless task switching.
- **Context Switching**: Efficient register state management using PendSV (specifically for ARM Cortex-M architecture).
- **Smart Delay (Non-Blocking)**: `os_delay` function that puts tasks to sleep, yielding CPU time to other ready tasks.
- **Power Management**: Utilizes the `WFI` (Wait For Interrupt) instruction in the Idle Task to conserve battery life.
- **Synchronization (Mutex)**: Prevents race conditions when accessing shared resources (e.g., UART/Serial).
- **Inter-Task Communication (Message Queues)**: Reliable messaging mechanism for data exchange between tasks.
- **Hardware Abstraction Layer (HAL)**: Modular architecture separating OS logic from hardware-specific registers.

## 🛠️ Technical Specifications
- **Target Architecture**: ARM Cortex-M3.
- **Simulation Platform**: QEMU (Board: `lm3s6965evb`).
- **Programming Languages**: C (C11) & ARM Assembly.
- **Toolchain**: GNU Arm Embedded Toolchain (`gcc-arm-none-eabi`).

## 🚀 Getting Started

### Prerequisites (Ubuntu)
Ensure the toolchain and emulator are installed:
```bash
sudo apt update
sudo apt install gcc-arm-none-eabi build-essential qemu-system-arm


Tentu, Gabriel! Ini adalah langkah terakhir yang sangat penting untuk memastikan proyek MicroTech kamu terlihat profesional di mata pengembang internasional.

Berikut adalah versi Bahasa Inggris untuk README.md dan LICENSE yang sudah disesuaikan dengan tahun 2026 dan identitas kamu.

1. File: README.md (English Version)
Silakan salin seluruh teks di bawah ini ke dalam file README.md kamu.

Markdown
# MicroTech OS
A lightweight, open-source Real-Time Operating System (RTOS) designed for microcontrollers and embedded systems.

MicroTech OS is built from the ground up to provide maximum efficiency on resource-constrained devices. It focuses on portability, preemptive multitasking, and intelligent power management.

## ✨ Key Features
- **Preemptive Multitasking**: Round-Robin scheduling algorithm for seamless task switching.
- **Context Switching**: Efficient register state management using PendSV (specifically for ARM Cortex-M architecture).
- **Smart Delay (Non-Blocking)**: `os_delay` function that puts tasks to sleep, yielding CPU time to other ready tasks.
- **Power Management**: Utilizes the `WFI` (Wait For Interrupt) instruction in the Idle Task to conserve battery life.
- **Synchronization (Mutex)**: Prevents race conditions when accessing shared resources (e.g., UART/Serial).
- **Inter-Task Communication (Message Queues)**: Reliable messaging mechanism for data exchange between tasks.
- **Hardware Abstraction Layer (HAL)**: Modular architecture separating OS logic from hardware-specific registers.

## 🛠️ Technical Specifications
- **Target Architecture**: ARM Cortex-M3.
- **Simulation Platform**: QEMU (Board: `lm3s6965evb`).
- **Programming Languages**: C (C11) & ARM Assembly.
- **Toolchain**: GNU Arm Embedded Toolchain (`gcc-arm-none-eabi`).

## 🚀 Getting Started

### Prerequisites (Ubuntu)
Ensure the toolchain and emulator are installed:
```bash
sudo apt update
sudo apt install gcc-arm-none-eabi build-essential qemu-system-arm
Build & Run
Compile the Project:

Bash
make
This will generate the microtech.elf executable.

Run in Emulator:

Bash
qemu-system-arm -M lm3s6965evb -cpu cortex-m3 -nographic -kernel microtech.elf
Exit QEMU:
Press Ctrl + A, then release, then press X.

📂 Project Structure
app/: User-level application (contains main.c).

arch/: Architecture-specific code (Startup, Booting, Vector Table).

core/: OS Kernel (Scheduler, Task Management, Mutex, Queue, SysTick).

drivers/: Basic peripheral drivers (UART).

hal/: Hardware Abstraction Layer (GPIO implementation).

linker.ld: Linker script for memory mapping.

Makefile: Build automation system.