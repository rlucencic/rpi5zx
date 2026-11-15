# rpi5zx: the ZX Spectrum 128K, +2 and +3 on the Raspberry Pi 5.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/rpi5zx --help
#
# The Spectrum itself is esp32zx's (../esp32zx/components/zx, platform
# independent), the runtime rpi5emu's (../rpi5emu), the Z80 and the uPD765
# esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(rpi5zx C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32ZX_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32zx" CACHE PATH "esp32zx checkout: the Spectrum")
if(NOT EXISTS "${ESP32ZX_DIR}/components/zx/include/zx.h")
    message(FATAL_ERROR "No esp32zx at ${ESP32ZX_DIR}: clone github.com/rlucencic/esp32zx beside rpi5zx")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../rpi5emu" rpi5emu)

file(GLOB ZX_SOURCES "${ESP32ZX_DIR}/components/zx/*.c")
add_executable(rpi5zx
    src/main.c
    src/settings.c
    src/rom_store.c
    ${ZX_SOURCES})
target_include_directories(rpi5zx PRIVATE
    src
    "${ESP32ZX_DIR}/components/zx/include"
    "${ESP32ZX_DIR}/components/zx")
# The Z80 with the ULA's memory contention, as esp32zx's
target_compile_definitions(rpi5zx PRIVATE CONFIG_Z80_CONTENTION=1)
rpi5emu_add_cores(rpi5zx z80 upd765 diskspace)
target_link_libraries(rpi5zx PRIVATE rpi5emu)
target_compile_options(rpi5zx PRIVATE -Wall -Wextra -Wno-unused-parameter)

install(TARGETS rpi5zx)
