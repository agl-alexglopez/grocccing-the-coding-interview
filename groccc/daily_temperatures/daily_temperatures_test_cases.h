#ifndef DAILY_TEMPERATURES
#define DAILY_TEMPERATURES

#include "../test_case_generator.h"

struct Daily_temperatures_input
{
    int *temps;
    int temps_count;
};

struct Daily_temperatures_output
{
    int *days_until_warmer_temps;
    int days_count;
};

TCG_tests_begin(daily_temperatures_tests,
                struct Daily_temperatures_input,
                struct Daily_temperatures_output)
TCG_test_case("standard gaps", {
    .input = {
        .temps = (int[8]){73, 74, 75, 71, 69, 72, 76, 73},
        .temps_count = 8,
    },
    .output = {
        .days_until_warmer_temps = (int[8]){1, 1, 4, 2, 1, 1, 0, 0},
        .days_count = 8,
    },
})
TCG_tests_end(daily_temperatures_tests);

#endif /* DAILY_TEMPERATURES */
