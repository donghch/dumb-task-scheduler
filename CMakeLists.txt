cmake_minimum_required(VERSION 3.10)

project(Scheduler C ASM) # Add ASM for startup files if you use assembly

add_subdirectory(src)
add_subdirectory(tests)

add_custom_target(build ALL DEPENDS dist)
