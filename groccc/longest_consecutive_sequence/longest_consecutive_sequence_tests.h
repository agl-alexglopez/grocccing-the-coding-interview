#ifndef LONGEST_CONSECUTIVE_SEQUENCE_TESTS_H
#define LONGEST_CONSECUTIVE_SEQUENCE_TESTS_H

#include "utility/test_case_generator.h"

#include "ccc/flat_buffer.h"

TCG_tests(longest_consecutive_sequence_tests,
    ((struct Longest_consecutive_sequence_input {
        CCC_Flat_buffer nums;
    }){}),
    ((struct Longest_consecutive_sequence_output {
        /** The longest sequence of consecutive increasing integers found. */
        int longest;
    }){}),
    TCG_test("empty input", {
        .input = {
            .nums = CCC_flat_buffer_default(int),
        },
        .output = {
            .longest = 0,
        },
    }),
    TCG_test("single element", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                1,
                (int[1]){42}
            ),
        },
        .output = {
            .longest = 1,
        },
    }),
    TCG_test("all duplicates", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                6,
                (int[6]){5,5,5,5,5,5}
            ),
        },
        .output = {
            .longest = 1,
        },
    }),
    TCG_test("already sorted consecutive", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                7,
                (int[7]){10,11,12,13,14,15,16}
            ),
        },
        .output = {
            .longest = 7,
        },
    }),
    TCG_test("reverse sorted consecutive", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                7,
                (int[7]){16,15,14,13,12,11,10}
            ),
        },
        .output = {
            .longest = 7,
        },
    }),
    TCG_test("negative consecutive", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                7,
                (int[7]){-3,-2,-1,0,1,50,100}
            ),
        },
        .output = {
            .longest = 5,
        },
    }),
    TCG_test("mixed positives and negatives", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                10,
                (int[10]){-10, 100, -8, -7, -6, 5, 4, 3, 2, 1}
            ),
        },
        .output = {
            .longest = 5,
        },
    }),
    TCG_test("multiple sequences choose longest", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                12,
                (int[12]){1,2,3,10,11,12,13,50,51,52,100,7}
            ),
        },
        .output = {
            .longest = 4,
        },
    }),
    TCG_test("gap of size one", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                8,
                (int[8]){1,2,3,5,6,7,10,11}
            ),
        },
        .output = {
            .longest = 3,
        },
    }),
    TCG_test("large range but sparse", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                6,
                (int[6]){-1000,500,999,1000,1001,-999}
            ),
        },
        .output = {
            .longest = 3,
        },
    }),
    TCG_test("mixed duplicates in sequences", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                12,
                (int[12]){2,2,3,3,4,4,10,11,11,12,12,13}
            ),
        },
        .output = {
            .longest = 4,
        },
    }),
    TCG_test("wide scattered data with one small sequence", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                10,
                (int[10]){1000,-50,9999,3,1,300,4,700,2,800}
            ),
        },
        .output = {
            .longest = 4,
        },
    }),
    TCG_test("sequence at the end of array", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                9,
                (int[9]){50,9,8,100,200,3,2,1,4}
            ),
        },
        .output = {
            .longest = 4,
        },
    }),
    TCG_test("4 consecutive", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                6,
                (int[6]){100, 4, 200, 1, 3, 2}
            ),
        },
        .output = {
            .longest = 4,
        },
    }),
    TCG_test("9 consecutive", {
        .input = {
            .nums = CCC_flat_buffer_with_storage(
                10,
                (int[10]){0,3,7,2,5,8,4,6,0,1}
            ),
        },
        .output = {
            .longest = 9,
        },
    }),
);

#endif /* LONGEST_CONSECUTIVE_SEQUENCE_TESTS_H */
