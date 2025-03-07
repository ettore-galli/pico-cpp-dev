cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pio_pwm_example)

pico_sdk_init()

add_executable(pio_pwm_example main.c)

pico_generate_pio_header(pio_pwm_example ${CMAKE_CURRENT_LIST_DIR}/pio_pwm.pio)

target_link_libraries(pio_pwm_example pico_stdlib hardware_pio)

pico_enable_stdio_usb(pio_pwm_example 1)
pico_enable_stdio_uart(pio_pwm_example 1)

pico_add_extra_outputs(pio_pwm_example)