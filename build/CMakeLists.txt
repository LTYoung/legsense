cmake_minimum_required(VERSION 3.13)

# import SDK
include(/tools/pico-sdk/pico_sdk_init.cmake)

project(legsense)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# initialize SDK
pico_sdk_init()

add_executable(main
	../src/main.cpp
	)

# add libs
target_link_libraries(main pico_stdlib)

# create ELF
pico_add_extra_outputs(main)
