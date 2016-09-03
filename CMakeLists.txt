cmake_minimum_required(VERSION 2.6)
project(path)

add_executable(path main.c)

install(TARGETS path RUNTIME DESTINATION bin)
