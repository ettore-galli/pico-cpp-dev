cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_sound)

pico_sdk_init()

add_executable(pico_sound main.cpp)

pico_generate_pio_header(pico_sound ${CMAKE_CURRENT_SOURCE_DIR}/pio_sound.pio)

target_link_libraries(pico_sound pico_stdlib hardware_pio hardware_adc)

pico_enable_stdio_usb(pico_sound 1)
pico_enable_stdio_uart(pico_sound 0)

pico_add_extra_outputs(pico_sound)