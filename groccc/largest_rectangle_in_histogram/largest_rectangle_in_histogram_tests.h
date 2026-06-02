#ifndef LARGEST_RECTANGLE_IN_HISTOGRAM_TESTS_H
#define LARGEST_RECTANGLE_IN_HISTOGRAM_TESTS_H

#include "utility/test_case_generator.h"

#include "ccc/flat_buffer.h"

TCG_tests(largest_rectangle_in_histogram_tests,
    ((struct Largest_rectangle_in_histogram_input{
        CCC_Flat_buffer heights;
    }){}),
    ((struct Largest_rectangle_in_histogram_output{
        int largest_area;
    }){}),
    TCG_test("area 10", {
        .input = {
            .heights = CCC_flat_buffer_with_storage(
                6, (int[6]){2, 1, 5, 6, 2, 3}
            ),
        },
        .output = {
            .largest_area = 10,
        },
    }),
    TCG_test("area 4", {
        .input = {
            .heights = CCC_flat_buffer_with_storage(
                2, (int[3]){2, 4}
            ),
        },
        .output = {
            .largest_area = 4,
        },
    }),
    TCG_test("area all bars at height 2", {
        .input = {
            .heights = CCC_flat_buffer_with_storage(
                6, (int[6]){2, 2, 5, 6, 2, 3}
            ),
        },
        .output = {
            .largest_area = 12,
        },
    }),
);

#endif /* LARGEST_RECTANGLE_IN_HISTOGRAM_TESTS_H */
