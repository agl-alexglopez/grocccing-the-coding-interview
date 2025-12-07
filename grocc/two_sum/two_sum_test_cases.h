#include <stddef.h>

#include "../test_case_generator.h"

struct Two_sum_input
{
    int target;
    int const *nums;
    size_t nums_count;
};

struct Two_sum_output
{
    int addends[2];
};

TCG_begin_test_cases(two_sum_tests, struct Two_sum_input, struct Two_sum_output)

TCG_begin_test_case("positives and negatives", {
    .target = 15,
    .nums = (int[10]){1, 3, -980, 6, 7, 13, 44, 32, 995, -1,},
    .nums_count = 10,
})
TCG_end_test_case({
    .addends = {8, 2}
})

TCG_end_test_cases(two_sum_tests);
