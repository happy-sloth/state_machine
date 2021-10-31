cmake_minimum_required(VERSION 3.5)

project(state_machine LANGUAGES C)

add_executable(state_machine main.c)

# Link fsm lib
add_subdirectory(lib)
target_link_libraries(${PROJECT_NAME} fsm_lib)
