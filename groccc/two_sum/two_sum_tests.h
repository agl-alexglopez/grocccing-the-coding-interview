#ifndef TWO_SUM_TESTS_H
#define TWO_SUM_TESTS_H
#include <stddef.h>

#include "utility/test_case_generator.h"

#include "ccc/flat_buffer.h"

TCG_tests(two_sum_tests,
    ((struct Two_sum_input {
        int target;
        CCC_Flat_buffer const nums;
    }){}),
    ((struct Two_sum_output {
        size_t addends[2];
    }){}),
    TCG_test("empty", {
        .input = {},
        .output = {},
    }),
    TCG_test("negatives", {
        .input = {
            .target = 15,
            .nums = CCC_flat_buffer_with_storage(
                10,
                (int[10]){1, 3, -980, 6, 7, 13, 44, 32, 995, -1,}
            ),
        },
        .output = {
            .addends = {8, 2},
        }
    }),
    TCG_test("no solution", {
        .input = {
            .target = 2,
            .nums = CCC_flat_buffer_with_storage(
                4,
                (int[4]){1, 3, 4, 5}
            ),
        },
        .output = {},
    }),
    TCG_test("multiple choices pick lowest indices", {
        .input = {
            .target = 9,
            .nums = CCC_flat_buffer_with_storage(
                6,
                (int[6]){2, 7, 11, 15, 7, 2}
            ),
        },
        .output = {
            .addends = {0, 1},
        },
    }),
    TCG_test("duplicate values different pair", {
        .input = {
            .target = 10,
            .nums = CCC_flat_buffer_with_storage(
                7,
                (int[7]){5, 5, 3, 7, 5, 2, 8}
            ),
        },
        .output = {
            .addends = {0, 1},
        },
    }),
);
#endif /* TWO_SUM_TESTS_H */
