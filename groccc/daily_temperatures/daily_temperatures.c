#include <stddef.h>
#include <string.h>

#define FLAT_BUFFER_USING_NAMESPACE_CCC
#define TRAITS_USING_NAMESPACE_CCC
#include "ccc/flat_buffer.h"
#include "ccc/traits.h"
#include "ccc/types.h"

#include "daily_temperatures_tests.h"
#include "utility/allocators.h"
#include "utility/defer.h"
#include "utility/loggers.h"
#include "utility/test_case_generator.h"

static inline bool
are_equal(Flat_buffer const *const a, Flat_buffer const *const b) {
    if (count(a).count != count(b).count) {
        return false;
    }
    if (!count(a).count) {
        return true;
    }
    return memcmp(begin(a), begin(b), flat_buffer_count_bytes(a).count) == 0;
}

static struct Daily_temperatures_output
daily_temperatures(
    struct Daily_temperatures_input *const input,
    CCC_Allocator const *const allocator
) {
    size_t const end = count(&input->temperatures).count;
    flat_buffer_count_set(&input->days_until_warmer_temperature_result, end);
    Flat_buffer index_stack = flat_buffer_with_capacity(int, *allocator, end);
    defer {
        clear_and_free(&index_stack, &(CCC_Destructor){}, allocator);
    }
    for (size_t i = 0; i < end; ++i) {
        int const *const cur_temp = flat_buffer_at(&input->temperatures, i);
        while (!is_empty(&index_stack)
               && *cur_temp > *flat_buffer_as(
                      &input->temperatures,
                      int,
                      *flat_buffer_back_as(&index_stack, int)
                  )) {
            int const index = *flat_buffer_back_as(&index_stack, int);
            *flat_buffer_as(
                &input->days_until_warmer_temperature_result, int, index
            ) = (int)i - index;
            (void)pop_back(&index_stack);
        }
        (void)push_back(&index_stack, &i, allocator);
    }
    return (struct Daily_temperatures_output){
        input->days_until_warmer_temperature_result,
    };
}

int
main(void) {
    TCG_Count passed = 0;
    TCG_for_each_test_case(daily_temperatures_tests, {
        struct Daily_temperatures_output const output = daily_temperatures(
            &TCG_test_case_input(daily_temperatures_tests), &std_allocator
        );
        struct Daily_temperatures_output const *const correct_output
            = &TCG_test_case_output(daily_temperatures_tests);
        if (!are_equal(
                &output.days_until_warmer_temperature,
                &correct_output->days_until_warmer_temperature
            )) {
            logfail(daily_temperatures_tests);
        } else {
            ++passed;
        }
    });
    return TCG_tests_status(daily_temperatures_tests, passed);
}
