# sdlzx: the ZX Spectrum 128K, +2 and +3 with SDL 3.
#
#   cmake -S . -B build -G Ninja && cmake --build build
#   build/sdlzx --help
#
# The Spectrum itself is esp32zx's (../esp32zx/components/zx, platform
# independent), the runtime sdlemu's (../sdlemu), the Z80 and the uPD765
# esp32emu's (../esp32emu): all four cloned side by side.
cmake_minimum_required(VERSION 3.20)
project(sdlzx C)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif()

set(ESP32ZX_DIR "${CMAKE_CURRENT_LIST_DIR}/../esp32zx" CACHE PATH "esp32zx checkout: the Spectrum")
if(NOT EXISTS "${ESP32ZX_DIR}/components/zx/include/zx.h")
    message(FATAL_ERROR "No esp32zx at ${ESP32ZX_DIR}: clone github.com/rlucencic/esp32zx beside sdlzx")
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../sdlemu" sdlemu)

file(GLOB ZX_SOURCES "${ESP32ZX_DIR}/components/zx/*.c")
add_executable(sdlzx
    src/main.c
    src/settings.c
    src/rom_store.c
    ${ZX_SOURCES})
target_include_directories(sdlzx PRIVATE
    src
    "${ESP32ZX_DIR}/components/zx/include"
    "${ESP32ZX_DIR}/components/zx")
# The Z80 with the ULA's memory contention, as esp32zx's
target_compile_definitions(sdlzx PRIVATE CONFIG_Z80_CONTENTION=1)
sdlemu_add_cores(sdlzx z80 upd765 diskspace)
target_link_libraries(sdlzx PRIVATE sdlemu)
target_compile_options(sdlzx PRIVATE -Wall -Wextra -Wno-unused-parameter)

install(TARGETS sdlzx)
