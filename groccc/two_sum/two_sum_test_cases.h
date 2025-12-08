#ifndef TWO_SUM_TEST_CASES_H
#define TWO_SUM_TEST_CASES_H
#include <stddef.h>

#include "../test_case_generator.h"

struct Two_sum_input
{
    int target;
    int const *const nums;
    size_t nums_count;
};

struct Two_sum_output
{
    int addends[2];
};

TCG_tests_begin(two_sum_tests, struct Two_sum_input, struct Two_sum_output)
TCG_test_case("empty", {
    .input = {},
    .output = {
        .addends = {-1, -1}
    },
})
TCG_test_case("negatives", {
    .input = {
        .target = 15,
        .nums = (int[10]){1, 3, -980, 6, 7, 13, 44, 32, 995, -1,},
        .nums_count = 10,
    },
    .output = {
        .addends = {8, 2},
    }
})
TCG_test_case("no solution", {
    .input = {
        .target = 2,
        .nums = (int[4]){1, 3, 4, 5},
        .nums_count = 4,
    },
    .output = {
        .addends = {-1, -1}
    },
})
TCG_tests_end(two_sum_tests);
#endif /* TWO_SUM_TEST_CASES_H */
