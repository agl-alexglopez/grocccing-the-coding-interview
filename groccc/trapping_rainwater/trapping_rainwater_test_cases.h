#ifndef TRAPPING_RAINWATER_TEST_CASES_H
#define TRAPPING_RAINWATER_TEST_CASES_H

#include "../test_case_generator.h"

struct Trapping_rainwater_input
{
    int *heights;
    int heights_count;
};

struct Trapping_rainwater_output
{
    int trapped_water_units;
};

TCG_tests_begin(trapping_rainwater_tests, struct Trapping_rainwater_input,
                struct Trapping_rainwater_output)
TCG_test_case("empty", {.input = {}, .output = {}})
TCG_test_case("trap peak", {
    .input = {
        .heights = (int[3]){0, 9, 0},
        .heights_count = 3,
    },
    .output = {
        .trapped_water_units = 0,
    }
})
TCG_test_case("trap valley", {
    .input = {
        .heights = (int[3]){9, 0, 9},
        .heights_count = 3,
    },
    .output = {
        .trapped_water_units = 9,
    }
})
TCG_test_case("trap 6", {
    .input = {
        .heights = (int[12]){0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1},
        .heights_count = 12,
    },
    .output = {
        .trapped_water_units = 6,
    },
})
TCG_tests_end(trapping_rainwater_tests);

#endif /* TRAPPING_RAINWATER_TEST_CASES_H */
