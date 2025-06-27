target_sources(
    ${PROJECT_NAME}
    PRIVATE
    scheduler.s
    startup.c
    startup.s
    systick.c
)

add_subdirectory(
    types
)