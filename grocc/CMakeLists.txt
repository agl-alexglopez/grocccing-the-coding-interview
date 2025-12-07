cmake_minimum_required(VERSION 3.23)
project("grocc problems"
    VERSION 1.0.0
    LANGUAGES C
    DESCRIPTION "Problems to grocc."
)

######################### Fetch C Container Collection ########################

include(FetchContent)
FetchContent_Declare(
  ccc
  URL https://github.com/agl-alexglopez/ccc/releases/download/v0.40.0/ccc-v0.40.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP FALSE # CMake may raise a warning to set this.
)
FetchContent_MakeAvailable(ccc)

#########################   Create Problems Target   ##########################

add_custom_target(problems)

#######################   Add Test Case Generator Helper   ####################

add_library(test_case_generator INTERFACE test_case_generator.h)
add_dependencies(problems test_case_generator)

#######################   Macro for Adding Problem Files   ####################

macro(add_problem PROBLEM_NAME)
    add_library(${PROBLEM_NAME}_test_cases INTERFACE ${PROBLEM_NAME}/${PROBLEM_NAME}_test_cases.h)
    add_executable(${PROBLEM_NAME} ${PROBLEM_NAME}/${PROBLEM_NAME}.c)
    target_link_libraries(${PROBLEM_NAME}
        PRIVATE
            ccc
            test_case_generator
            ${PROBLEM_NAME}_test_cases
    )
endmacro()

###########################        Problem List      ##########################

add_problem(two_sum)
