
cmake_minimum_required(VERSION 3.10)

project(tests C)

# set test sources
SET(TEST_SOURCE_DIR src)
SET(TEST_INCLUDE_DIR inc)
file(GLOB_RECURSE SOURCES ${TEST_SOURCE_DIR}/*.c)
file(GLOB_RECURSE HEADERS ${TEST_INCLUDE_DIR}/*.h)

#set code sources
SET(SOURCE_DIR ../src/src)
SET(INCLUDE_DIR ../src/inc)
file(GLOB_RECURSE CODE_SOURCES ${SOURCE_DIR}/types/*.c)
file(GLOB_RECURSE CODE_HEADERS ${INCLUDE_DIR}/*.h)

add_executable(tests ${SOURCES} ${CODE_SOURCES})

target_include_directories(tests PUBLIC ${TEST_INCLUDE_DIR} ${INCLUDE_DIR})
target_compile_options(tests PRIVATE -g)