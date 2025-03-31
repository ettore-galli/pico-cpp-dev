cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(toyorgan)

pico_sdk_init()

set(SOURCES
    main.cpp
    toyorgan.cpp
)

set(HEADERS
    toyorgan.h
)

add_executable(toyorgan ${SOURCES} ${HEADERS})

pico_generate_pio_header(toyorgan ${CMAKE_CURRENT_SOURCE_DIR}/toyorgan.pio)

target_link_libraries(toyorgan pico_stdlib hardware_pio hardware_adc)

pico_enable_stdio_usb(toyorgan 1)
pico_enable_stdio_uart(toyorgan 0)

pico_add_extra_outputs(toyorgan)