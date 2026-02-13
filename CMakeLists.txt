cmake_minimum_required(VERSION 4.1)
project(hw1 C)

set(CMAKE_C_STANDARD 11)

add_executable(hw1 src/main.c
        src/main.c
        src/print_fib.c
        src/print_primes.c
        header/print_fib.h
        header/print_primes.h)
