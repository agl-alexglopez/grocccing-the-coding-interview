#ifndef TRAPPING_RAINWATER_TESTS_H
#define TRAPPING_RAINWATER_TESTS_H

#include "ccc/flat_buffer.h"

#include "utility/test_case_generator.h"

TCG_tests(trapping_rainwater_tests,
    ((struct Trapping_rainwater_input {
        CCC_Flat_buffer heights;
    }){}),
    ((struct Trapping_rainwater_output {
        int trapped_water_units;
    }){}),
    TCG_test("empty", {.input = {}, .output = {}}),
    TCG_test("trap peak", {
        .input = {
            .heights = CCC_flat_buffer_with_storage(
                3,
                (int[3]){0, 9, 0}
            ),
        },
        .output = {
            .trapped_water_units = 0,
        }
    }),
    TCG_test("trap valley", {
        .input = {
            .heights = CCC_flat_buffer_with_storage(
                3,
                (int[3]){9, 0, 9}
            ),
        },
        .output = {
            .trapped_water_units = 9,
        }
    }),
    TCG_test("trap 6", {
        .input = {
            .heights = CCC_flat_buffer_with_storage(
                12,
                (int[12]){0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}
            ),
        },
        .output = {
            .trapped_water_units = 6,
        },
    }),
    TCG_test("trap 10", {
        .input = {
            .heights = CCC_flat_buffer_with_storage(
                8,
                (int[8]){4, 2, 0, 3, 2, 5, 1, 2}
            ),
        },
        .output = {
            .trapped_water_units = 10,
        }
    }),
    TCG_test("trap pockets on way to peak", {
        .input = {
            .heights = CCC_flat_buffer_with_storage(
                7,
                (int[7]){2, 1, 4, 7, 4, 1, 2}
            ),
        },
        .output = {
            .trapped_water_units = 2,
        }
    }),
    TCG_test("trap pockets on way to valley", {
        .input = {
            .heights = CCC_flat_buffer_with_storage(
                7,
                (int[7]){7, 1, 4, 3, 2, 1, 0}
            ),
        },
        .output = {
            .trapped_water_units = 3,
        }
    }),
);

#endif /* TRAPPING_RAINWATER_TESTS_H */
