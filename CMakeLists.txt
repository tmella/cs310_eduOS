cmake_minimum_required(VERSION 3.20)
project(cswk C)

set(CMAKE_C_STANDARD 99)

add_executable(cswk main.c kernel/irq.h kernel/irq.c drivers/keyboard.h drivers/keyboard.c kernel/process.h kernel/process_scheduler.h utils/queue.h utils/Memory.h kernel/process_scheduler.c utils/queue.c kernel/syscalls.h kernel/exit.c kernel/exit.h stdlib/stdlib.h stdlib/stdlib.c kernel/memory/page.h kernel/timer.h kernel/memory/heap.h)
