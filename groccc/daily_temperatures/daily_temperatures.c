#include "daily_temperatures_test_cases.h"

/* TODO: solve daily_temperatures */
static struct Daily_temperatures_output
daily_temperatures(struct Daily_temperatures_input *input)
{
    return (struct Daily_temperatures_output){};
}

int
main(void)
{
    TCG_for_each_test_case(daily_temperatures_tests, {
        /* TODO: Use these to check your output against the correct output. */
        struct Daily_temperatures_output const output 
            = daily_temperatures(&TCG_test_case_input(daily_temperatures_tests));
        struct Daily_temperatures_output const *const correct_output 
            = &TCG_test_case_output(daily_temperatures_tests);
    });
    return 0;
}
