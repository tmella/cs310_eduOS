cmake_minimum_required(VERSION 3.20)
project(cswk C)

set(CMAKE_C_STANDARD 99)

add_executable(cswk main.c kernel/irq.h kernel/irq.c drivers/keyboard.h drivers/keyboard.c)
