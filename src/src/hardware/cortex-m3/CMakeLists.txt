target_sources(
    ${PROJECT_NAME}
    PRIVATE
    scheduler.s
    startup.c
    startup.s
    systick.c
    syscall.c
    syscall.s
)

add_subdirectory(
    types
)