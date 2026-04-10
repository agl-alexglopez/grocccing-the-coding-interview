cmake_minimum_required(VERSION 3.23)
project("groccc-problems"
    VERSION 1.0.0
    LANGUAGES C
    DESCRIPTION "Problems to groccc."
)

######################### Fetch C Container Collection ########################

include(FetchContent)
FetchContent_Declare(
    ccc
    URL https://github.com/skeletoss/ccc/releases/download/v0.77.4/ccc-v0.77.4.zip
    URL_HASH SHA256=f9626e8707e0a428aaaba8f2bd68c50b7addc09868c2a363f4b9877db510e79c
    DOWNLOAD_EXTRACT_TIMESTAMP FALSE
    SYSTEM
)
FetchContent_MakeAvailable(ccc)
target_compile_options(ccc PRIVATE "-w")
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
    SYSTEM
)
FetchContent_MakeAvailable(str_view)
target_compile_options(str_view PRIVATE "-w")

#########################   Create Problems Target   ##########################

add_custom_target(problems)

########################     Add Problem Runner     ###########################

add_executable(run_problems run_problems.c)
target_link_libraries(run_problems str_view::str_view loggers test_case_generator)
add_dependencies(problems run_problems)

#######################   Macro for Adding Problem Files   ####################

macro(add_problem PROBLEM_NAME)
    add_library(${PROBLEM_NAME}_tests INTERFACE ${PROBLEM_NAME}/${PROBLEM_NAME}_tests.h)
    target_link_libraries(${PROBLEM_NAME}_tests INTERFACE ccc::ccc str_view::str_view test_case_generator)
    add_executable(${PROBLEM_NAME} ${PROBLEM_NAME}/${PROBLEM_NAME}.c)
    target_link_libraries(${PROBLEM_NAME}
        PRIVATE
            ccc::ccc
            str_view::str_view
            string_arena
            test_case_generator
            loggers
            allocators
            hash_helpers
            defer
            ${PROBLEM_NAME}_tests
    )
    set_target_properties(${PROBLEM_NAME}
        PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY
                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/problems
    )
    add_dependencies(problems ${PROBLEM_NAME})
endmacro()

###########################        Problem List      ##########################

# WARNING! Do not add any comments or text below this comment. A provided script
# appends new coding problem targets to the bottom of this file by creating the
# necessary files and folders and using the below macro. The script should check
# if problems are unique so this list should not have repeats.

add_problem(two_sum)
add_problem(trapping_rainwater)
add_problem(daily_temperatures)
add_problem(longest_consecutive_sequence)
add_problem(group_anagrams)
add_problem(largest_rectangle_in_histogram)
add_problem(top_k_frequent_elements)
add_problem(valid_sudoku)
add_problem(sort_an_array)
