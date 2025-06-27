cmake_minimum_required(VERSION 3.20)

project(dist C ASM)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

# Set compiler and flags
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)
# -nostdlib is used here
set(CMAKE_C_FLAGS "-mcpu=cortex-m3 -mthumb -Wall -O0 -g")
set(CMAKE_ASM_FLAGS "-mcpu=cortex-m3 -mthumb -g")
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

# Set project source files
set(HEADER_DIR inc)

add_executable(${PROJECT_NAME})
add_subdirectory(src)
target_include_directories(${PROJECT_NAME} PRIVATE ${HEADER_DIR})

# Set linker options
target_link_options(${PROJECT_NAME} PRIVATE -T${PROJECT_SOURCE_DIR}/linker.ld)
# Keep -nostdlib, and explicitly link libgcc
# target_link_options(${PROJECT_NAME} PRIVATE -nostdlib -lc -lnosys) # WRONG
set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS_NO_SHARED_LIBS TRUE)