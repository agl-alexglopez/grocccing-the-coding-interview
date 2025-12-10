#ifndef DAILY_TEMPERATURES_H
#define DAILY_TEMPERATURES_H

#include "ccc/buffer.h"

#include "../test_case_generator.h"

/** The input temperature buffer with convenience output solution buffer
provided. Because the daily temperatures problem specifies the return value
has an entry for each temperature, it is provided here. The result buffer
will be provided with capacity equivalent to temperatures but 0 count.

Note that the result buffer may be freely and trivially shallow copied and
returned from a function. The underlying static memory to which it points
does not move and metadata in the Buffer struct remains consistent. */
struct Daily_temperatures_input
{
    /** The input buffer of N temperatures. */
    CCC_Buffer temperatures;
    /** The return value for this problem of N entries representing the number
    of days until a warmer temperature from the day at that index. Has
    capacity equivalent to temperatures and initial count 0. May be shallow
    copied into output return struct safely. Underlying storage does not
    move. */
    CCC_Buffer days_until_warmer_temperature_result;
};

/** The correct output buffer of N entries corresponding to the temperature for
each day. Each entry at index i represents the number of days required to see
a warmer temperature than the temperature recorded at the input buffer. */
struct Daily_temperatures_output
{
    /** The output buffer of correct days until warmer temperatures. */
    CCC_Buffer days_until_warmer_temperature;
};

TCG_tests_begin(daily_temperatures_tests,
                struct Daily_temperatures_input,
                struct Daily_temperatures_output)

TCG_test_case("standard gaps", {
    .input = {
        .temperatures = CCC_buffer_initialize(
            ((int[8]){73, 74, 75, 71, 69, 72, 76, 73}),
            int,
            NULL,
            NULL,
            8,
            8
        ),
        .days_until_warmer_temperature_result = CCC_buffer_initialize(
            (int[8]){},
            int,
            NULL,
            NULL,
            8,
        ),
    },
    .output = {
        .days_until_warmer_temperature = CCC_buffer_initialize(
            ((int[8]){1, 1, 4, 2, 1, 1, 0, 0}),
            int,
            NULL,
            NULL,
            8,
            8
        ),
    },
})

TCG_tests_end(daily_temperatures_tests);

#endif /* DAILY_TEMPERATURES_H */
