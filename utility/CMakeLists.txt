cmake_minimum_required(VERSION 3.23)
project("groccc-utility"
    VERSION 1.0.0
    LANGUAGES C
    DESCRIPTION "Utility helpers to groccc problems."
)

##################   Add utility Available to All Tests   ###################

add_custom_target(utility)

add_library(loggers INTERFACE loggers.h)
target_include_directories(loggers INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>)
add_dependencies(utility loggers)

add_library(string_arena string_arena.h string_arena.c)
target_include_directories(string_arena PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>)
add_dependencies(utility string_arena)

add_library(allocators allocators.h allocators.c)
target_include_directories(allocators PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>)
target_link_libraries(allocators PUBLIC ccc::ccc)
add_dependencies(utility allocators)

add_library(hash_helpers hash_helpers.h hash_helpers.c)
target_include_directories(hash_helpers PUBLIC $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>)
target_link_libraries(hash_helpers PUBLIC ccc::ccc str_view::str_view)
add_dependencies(utility hash_helpers)

add_library(test_case_generator INTERFACE test_case_generator.h)
target_include_directories(test_case_generator INTERFACE $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}>)
add_dependencies(utility test_case_generator)
