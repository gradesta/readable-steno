cmake_minimum_required(VERSION 3.12)

include(../../pico-sdk/external/pico_sdk_import.cmake)

project(read_code C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_FLASH_SIZE_BYTES 16777216)
set(PICO_BOARD pico CACHE STRING "Board type")
set(PICO_SDK_FETCH_FROM_GIT 1)

pico_sdk_init()

add_executable(
    ${PROJECT_NAME}
    main.c
    led_driver.c
    keymap.c
    usb_descriptors.c
)

target_compile_definitions(${PROJECT_NAME} PRIVATE
    PICO_STDIO_USB=0
    PICO_STDIO_UART=0
)

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 0)  # Optional: disables UART output

pico_add_extra_outputs(${PROJECT_NAME})
target_link_libraries(
    ${PROJECT_NAME}
    pico_stdlib
    tinyusb_device
    tinyusb_board
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
