# This version gives us file sets which are great for library install.
cmake_minimum_required(VERSION 3.23)
project("groccc"
    VERSION 0.40.0
    LANGUAGES C
    DESCRIPTION "Ensure your time spent preparing for a coding interview is wasted. Do it in C."
)
# Specify that C23 should be used
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# For releases we only produce this and the source. No test or sample bloat.
add_subdirectory("${PROJECT_SOURCE_DIR}/utility")
add_subdirectory("${PROJECT_SOURCE_DIR}/${PROJECT_NAME}")
include(tools/scanners.cmake)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()


if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/debug/bin)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
endif()

######################### Fetch C Container Collection ########################

include(FetchContent)
FetchContent_Declare(
    ccc
    URL https://github.com/skeletoss/ccc/releases/download/v0.73.0/ccc-v0.73.0.zip
    URL_HASH SHA256=aa56aebfd4ba39aa5a1f060ec12f097349777f91ab9e5784dc9d62356dc5f6f0
    DOWNLOAD_EXTRACT_TIMESTAMP FALSE
)
FetchContent_MakeAvailable(ccc)
target_compile_options(ccc PRIVATE "-w")
get_target_property(ccc_SOURCE_DIR ccc SOURCE_DIR)
# We will leave this here to always be able to test CCC freestanding. But we
# won't define the cache variables or set the user configuration here. Only do
# that at the command line via -DCCC_USER_CONFIGURATION="ccc_configuration.h"
# or via a cache variable in CMakePresets.json.
target_include_directories(ccc PRIVATE
    ${CMAKE_SOURCE_DIR}/configuration
)

#########################   Fetch Str_view Library     ########################

include(FetchContent)
FetchContent_Declare(
    str_view
    URL https://github.com/skeletoss/str_view/releases/download/v0.7.1/str_view-v0.7.1.zip
    URL_HASH SHA256=43e1f3de16770542b40f832c2cf50adf7ea4a0b5a4eee19fc31c215b798ccc61
    DOWNLOAD_EXTRACT_TIMESTAMP FALSE
)
FetchContent_MakeAvailable(str_view)
target_compile_options(str_view PRIVATE "-w")
get_target_property(str_view_SOURCE_DIR str_view SOURCE_DIR)

