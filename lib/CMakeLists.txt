cmake_minimum_required(VERSION 3.5)

project(fsm_lib LANGUAGES C)

set(SOURCES state_machine.c)
set(HEADERS state_machine.h)

add_library(fsm_lib ${SOURCES}
                ${HEADERS}
                )
target_include_directories(fsm_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

