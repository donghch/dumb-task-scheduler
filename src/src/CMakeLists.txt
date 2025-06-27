add_subdirectory(hardware)
add_subdirectory(scheduling)
add_subdirectory(types)
target_sources(
    ${PROJECT_NAME} PRIVATE 
    main.c 
    scheduler.c 
    task.c
    tasks.c
)