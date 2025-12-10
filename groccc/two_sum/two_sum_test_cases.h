#ifndef TWO_SUM_TEST_CASES_H
#define TWO_SUM_TEST_CASES_H
#include <stddef.h>

#include "../test_case_generator.h"

#include "ccc/buffer.h"

struct Two_sum_input
{
    int target;
    CCC_Buffer const nums;
};

struct Two_sum_output
{
    size_t addends[2];
};

TCG_tests_begin(two_sum_tests, struct Two_sum_input, struct Two_sum_output)
TCG_test_case("empty", {
    .input = {},
    .output = {},
})
TCG_test_case("negatives", {
    .input = {
        .target = 15,
        .nums = CCC_buffer_initialize(
            ((int[10]){1, 3, -980, 6, 7, 13, 44, 32, 995, -1,}),
            int,
            NULL,
            NULL,
            10,
            10
        ),
    },
    .output = {
        .addends = {8, 2},
    }
})
TCG_test_case("no solution", {
    .input = {
        .target = 2,
        .nums = CCC_buffer_initialize(
            ((int[4]){1, 3, 4, 5}),
            int,
            NULL,
            NULL,
            4,
            4
        ),
    },
    .output = {},
})
TCG_test_case("multiple choices pick lowest indices", {
    .input = {
        .target = 9,
        .nums = CCC_buffer_initialize(
            ((int[6]){2, 7, 11, 15, 7, 2}),
            int,
            NULL,
            NULL,
            6,
            6
        ),
    },
    .output = {
        .addends = {0, 1},
    },
})
TCG_test_case("duplicate values different pair", {
    .input = {
        .target = 10,
        .nums = CCC_buffer_initialize(
            ((int[7]){5, 5, 3, 7, 5, 2, 8}),
            int,
            NULL,
            NULL,
            7,
            7
        ),
    },
    .output = {
        .addends = {0, 1},
    },
})
TCG_tests_end(two_sum_tests);
#endif /* TWO_SUM_TEST_CASES_H */
