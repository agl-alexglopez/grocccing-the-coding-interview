#ifndef LARGEST_RECTANGLE_IN_HISTOGRAM_TESTS_H
#define LARGEST_RECTANGLE_IN_HISTOGRAM_TESTS_H

#include "utility/test_case_generator.h"

#include "ccc/buffer.h"

struct Largest_rectangle_in_histogram_input
{
    CCC_Buffer heights;
};

struct Largest_rectangle_in_histogram_output
{
    int largest_area;
};

TCG_tests_begin(largest_rectangle_in_histogram_tests,
                struct Largest_rectangle_in_histogram_input,
                struct Largest_rectangle_in_histogram_output)
TCG_test_case("area 10", {
    .input = {
        .heights = CCC_buffer_with_compound_literal(
            6, (int[6]){2, 1, 5, 6, 2, 3}
        ),
    },
    .output = {
        .largest_area = 10,
    },
})
TCG_test_case("area 4", {
    .input = {
        .heights = CCC_buffer_with_compound_literal(
            2, (int[3]){2, 4}
        ),
    },
    .output = {
        .largest_area = 4,
    },
})
TCG_test_case("area all bars at height 2", {
    .input = {
        .heights = CCC_buffer_with_compound_literal(
            6, (int[6]){2, 2, 5, 6, 2, 3}
        ),
    },
    .output = {
        .largest_area = 12,
    },
})
TCG_tests_end(largest_rectangle_in_histogram_tests);

#endif /* LARGEST_RECTANGLE_IN_HISTOGRAM_TESTS_H */
