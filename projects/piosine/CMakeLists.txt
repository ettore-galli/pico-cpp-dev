cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_sine)

pico_sdk_init()

add_executable(pico_sine main.cpp)

pico_generate_pio_header(pico_sine ${CMAKE_CURRENT_SOURCE_DIR}/pio_sine.pio)

target_link_libraries(pico_sine pico_stdlib hardware_pio)

pico_enable_stdio_usb(pico_sine 1)
pico_enable_stdio_uart(pico_sine 0)

pico_add_extra_outputs(pico_sine)