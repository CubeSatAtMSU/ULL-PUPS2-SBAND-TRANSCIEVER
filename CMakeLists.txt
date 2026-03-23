cmake_minimum_required(VERSION 3.13)

# Name project
set(ProjectName s-band_transceiver_payload)

# Set any variables required for importing libraries
set(FREERTOS_KERNEL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib/FreeRTOS-Kernel)

# Import libraries
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Define project
project(${ProjectName} C CXX ASM)

# Initialize Pico SDK
pico_sdk_init()

# Define executable
add_executable(${ProjectName}
    config/config.c
    src/main.c
    src/core/message_queue.c
    src/freertos/init_tasks.c
    src/freertos/task_radio.c
    src/freertos/task_can.c
    src/freertos/task_housekeeping.c
    src/drivers/spi/bus_config.c
    src/drivers/radio/peripheral_lora1280.c
    src/drivers/radio/peripheral_rfm9x.c
    src/drivers/radio/sx1280_wrapper.cpp
    src/drivers/radio/SX1280.cpp
    src/drivers/radio/radio_hal.c
    src/drivers/can/peripheral_mcp2515.c
    src/subsystems/housekeeping/housekeeping.c
    src/protocols/protocol_rf_command.c
    src/protocols/protocol_spacecan.c
    src/protocols/spacecan_assembler.c
)

# Enable USB serial (set to 1 to enable)
pico_enable_stdio_usb(${ProjectName} 1)
pico_enable_stdio_uart(${ProjectName} 0)

# Add include paths
target_include_directories(${ProjectName}
    PRIVATE src
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/config
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link libraries
target_link_libraries(
    ${ProjectName}
    pico_stdlib
    hardware_spi
    FreeRTOS-Kernel-Heap4
    hardware_adc
    )

# Optional: Disable picotool if not needed
set(PICO_NO_FLASH 0)
set(PICO_COPY_TO_RAM 0)

# Create UF2, bin, and other outputs
pico_add_extra_outputs(${ProjectName})
