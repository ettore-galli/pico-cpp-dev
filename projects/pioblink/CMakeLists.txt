cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_led_blink)

pico_sdk_init()

add_executable(pico_led_blink main.cpp)

# Aggiungi il file PIO al progetto
pico_generate_pio_header(pico_led_blink ${CMAKE_CURRENT_SOURCE_DIR}/pio_blink.pio)

# Collega le librerie necessarie
target_link_libraries(pico_led_blink pico_stdlib hardware_pio)

# Abilita l'output USB
pico_enable_stdio_usb(pico_led_blink 1)
pico_enable_stdio_uart(pico_led_blink 0)

pico_add_extra_outputs(pico_led_blink)