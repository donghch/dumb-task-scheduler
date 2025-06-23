cmake_minimum_required(VERSION 3.10)

project(Scheduler C ASM) # Add ASM for startup files if you use assembly

# --- Toolchain Configuration ---
# Indicate a generic system for bare-metal
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Explicitly set the compiler for clarity and consistency
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc) # For assembly files like startup

# Define your linker script path (IMPORTANT: Adjust this to your actual path)
set(LINKER_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/linker.ld")

# --- Common Compiler Flags ---
# These are options for the compiler itself
add_compile_options(
    -march=armv7-m
    -mcpu=cortex-m3
    -mthumb
    -Wall             # Enable warnings
    -Wextra           # Enable extra warnings
    -Os               # Optimize for size
    -ffunction-sections # Place each function in its own section
    -fdata-sections   # Place each data in its own section
    -fno-common       # Prevent common symbols
    -fno-builtin      # Do not use built-in functions
    -g                # Generate debug information
)


# --- Source Files ---
# Add all your C, C++, and Assembly source files here
# You MUST have a startup file that provides the Reset_Handler and vector table.
# For bare-metal, a simple 'main.c' is not enough; the entry point is typically the Reset_Handler
# in a startup file.
add_executable(Scheduler
    src/main.c
    # src/startup_stm32f1xx.c # Uncomment and add your actual startup file here!
)

target_compile_options(Scheduler PRIVATE -S)