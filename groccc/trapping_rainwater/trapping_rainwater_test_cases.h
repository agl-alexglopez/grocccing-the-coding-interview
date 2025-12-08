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

/* clang-format off */
TCG_tests_begin(trapping_rainwater_tests, struct Trapping_rainwater_input,
                struct Trapping_rainwater_output)

TCG_test_case_begin("trap 6", {
    .heights = (int[12]){0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1},
    .heights_count = 12,
})
TCG_test_case_end({
    .trapped_water_units = 6,
})

TCG_tests_end(trapping_rainwater_tests);
/* clang-format on */

#endif /* TRAPPING_RAINWATER_TEST_CASES_H */
