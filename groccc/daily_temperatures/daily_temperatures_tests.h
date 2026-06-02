#ifndef DAILY_TEMPERATURES_TESTS_H
#define DAILY_TEMPERATURES_TESTS_H

#include "ccc/flat_buffer.h"

#include "utility/test_case_generator.h"

TCG_tests(daily_temperatures_tests,
    /** The input temperature buffer with convenience output solution buffer
    provided. Because the daily temperatures problem specifies the return value
    has an entry for each temperature, it is provided here. The result buffer
    will be provided with capacity equivalent to temperatures but 0 count.

    Note that the result buffer may be freely and trivially shallow copied and
    returned from a function. The underlying static memory to which it points
    does not move and metadata in the Flat_buffer struct remains consistent. */
    ((struct Daily_temperatures_input {
        /** The input buffer of N temperatures. */
        CCC_Flat_buffer temperatures;
        /** The return value for this problem of N entries representing the number
        of days until a warmer temperature from the day at that index. Has
        capacity equivalent to temperatures and initial count 0. May be shallow
        copied into output return struct safely. Underlying storage does not
        move. */
        CCC_Flat_buffer days_until_warmer_temperature_result;
    }){}),
    /** The correct output buffer of N entries corresponding to the temperature for
    each day. Each entry at index i represents the number of days required to see
    a warmer temperature than the temperature recorded at the input buffer. */
    ((struct Daily_temperatures_output {
        /** The output buffer of correct days until warmer temperatures. */
        CCC_Flat_buffer days_until_warmer_temperature;
    }){}),
    TCG_test("empty", {
        .input = {
            .temperatures = CCC_flat_buffer_default(int),
            .days_until_warmer_temperature_result = CCC_flat_buffer_default(int),
        },
        .output = {
            .days_until_warmer_temperature = CCC_flat_buffer_default(int),
        },
    }),
    TCG_test("single element", {
        .input = {
            .temperatures = CCC_flat_buffer_with_storage(
                1,
                (int[1]){42}
            ),
            .days_until_warmer_temperature_result = CCC_flat_buffer_with_storage(
                1,
                (int[1]){}
            ),
        },
        .output = {
            .days_until_warmer_temperature = CCC_flat_buffer_with_storage(
                1,
                (int[1]){0}
            ),
        },
    }),
    TCG_test("standard gaps", {
        .input = {
            .temperatures = CCC_flat_buffer_with_storage(
                8,
                (int[8]){73, 74, 75, 71, 69, 72, 76, 73}
            ),
            .days_until_warmer_temperature_result = CCC_flat_buffer_with_storage(
                8,
                (int[8]){}
            ),
        },
        .output = {
            .days_until_warmer_temperature = CCC_flat_buffer_with_storage(
                8,
                (int[8]){1, 1, 4, 2, 1, 1, 0, 0}
            ),
        },
    }),
    TCG_test("ascending with dips", {
        .input = {
            .temperatures = CCC_flat_buffer_with_storage(
                5,
                (int[5]){30, 60, 90, 40, 50}
            ),
            .days_until_warmer_temperature_result = CCC_flat_buffer_with_storage(
                5,
                (int[5]){}
            ),
        },
        .output = {
            .days_until_warmer_temperature = CCC_flat_buffer_with_storage(
                5,
                (int[5]){1, 1, 0, 1, 0}
            ),
        },
    }),
    TCG_test("all equal temperatures", {
        .input = {
            .temperatures = CCC_flat_buffer_with_storage(
                5,
                (int[5]){50, 50, 50, 50, 50}
            ),
            .days_until_warmer_temperature_result = CCC_flat_buffer_with_storage(
                5,
                (int[5]){}
            ),
        },
        .output = {
            .days_until_warmer_temperature = CCC_flat_buffer_with_storage(
                5,
                (int[5]){0, 0, 0, 0, 0}
            ),
        },
    }),
    TCG_test("strictly increasing", {
        .input = {
            .temperatures = CCC_flat_buffer_with_storage(
                6,
                (int[6]){10, 20, 30, 40, 50, 60}
            ),
            .days_until_warmer_temperature_result = CCC_flat_buffer_with_storage(
                6,
                (int[6]){}
            ),
        },
        .output = {
            .days_until_warmer_temperature = CCC_flat_buffer_with_storage(
                6,
                (int[6]){1, 1, 1, 1, 1, 0}
            ),
        },
    }),
    TCG_test("strictly decreasing", {
        .input = {
            .temperatures = CCC_flat_buffer_with_storage(
                6,
                (int[6]){90, 80, 70, 60, 50, 40}
            ),
            .days_until_warmer_temperature_result = CCC_flat_buffer_with_storage(
                6,
                (int[6]){}
            ),
        },
        .output = {
            .days_until_warmer_temperature = CCC_flat_buffer_with_storage(
                6,
                (int[6]){0, 0, 0, 0, 0, 0}
            ),
        },
    }),
    TCG_test("alternating high low", {
        .input = {
            .temperatures = CCC_flat_buffer_with_storage(
                8,
                (int[8]){50, 40, 50, 40, 50, 40, 50, 40}
            ),
            .days_until_warmer_temperature_result = CCC_flat_buffer_with_storage(
                8,
                (int[8]){}
            ),
        },
        .output = {
            .days_until_warmer_temperature = CCC_flat_buffer_with_storage(
                8,
                (int[8]){0, 1, 0, 1, 0, 1, 0, 0}
            ),
        },
    }),
    TCG_test("plateaus with rising edges", {
        .input = {
            .temperatures = CCC_flat_buffer_with_storage(
                7,
                (int[7]){30, 30, 30, 40, 40, 50, 50}
            ),
            .days_until_warmer_temperature_result = CCC_flat_buffer_with_storage(
                7,
                (int[7]){}
            ),
        },
        .output = {
            .days_until_warmer_temperature = CCC_flat_buffer_with_storage(
                7,
                (int[7]){3, 2, 1, 2, 1, 0, 0}
            ),
        },
    }),
    TCG_test("large valley then spike", {
        .input = {
            .temperatures = CCC_flat_buffer_with_storage(
                7,
                (int[7]){80, 60, 40, 20, 10, 70, 30}
            ),
            .days_until_warmer_temperature_result = CCC_flat_buffer_with_storage(
                7,
                (int[7]){}
            ),
        },
        .output = {
            .days_until_warmer_temperature = CCC_flat_buffer_with_storage(
                7,
                (int[7]){0, 4, 3, 2, 1, 0, 0}
            ),
        },
    }),
    TCG_test("jagged mixed pattern", {
        .input = {
            .temperatures = CCC_flat_buffer_with_storage(
                10,
                (int[10]){55, 58, 53, 54, 56, 52, 60, 59, 61, 50}
            ),
            .days_until_warmer_temperature_result = CCC_flat_buffer_with_storage(
                10,
                (int[10]){}
            ),
        },
        .output = {
            .days_until_warmer_temperature = CCC_flat_buffer_with_storage(
                10,
                (int[10]){1, 5, 1, 1, 2, 1, 2, 1, 0, 0}
            ),
        },
    }),
);

#endif /* DAILY_TEMPERATURES_TESTS_H */
