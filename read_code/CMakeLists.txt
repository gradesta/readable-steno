cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(read_code C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_FLASH_SIZE_BYTES 16777216)

pico_sdk_init()

add_executable(
    ${PROJECT_NAME}
    main.c
    led_driver.c
    keymap.c
)

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)  # Optional: disables UART output

pico_add_extra_outputs(${PROJECT_NAME})
target_link_libraries(
    ${PROJECT_NAME}
    pico_stdlib
)