cmake_minimum_required (VERSION 3.0)
project (shell)

set(CMAKE_CXX_STANDARD 11)

add_executable(shell main.cpp Executor.cpp Executor.h Parser.h Statement.h Terminal.h)