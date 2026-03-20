#ifndef SORT_AN_ARRAY_TESTS_H
#define SORT_AN_ARRAY_TESTS_H

#include "utility/test_case_generator.h"

#include "ccc/buffer.h"

struct Sort_an_array_input {
    CCC_Buffer ints;
};

struct Sort_an_array_output {
    CCC_Buffer sorted_ints;
};

TCG_tests_begin(sort_an_array_tests,
                struct Sort_an_array_input,
                struct Sort_an_array_output)

TCG_test_case("empty", {
    .input = {
        .ints = CCC_buffer_default(int),
    },
    .output = {
        .sorted_ints = CCC_buffer_default(int),
    },
})

TCG_test_case("reverse order", {
    .input = {
        .ints = CCC_buffer_with_storage(5, (int[5]){2,1,0,-1,-2}),
    },
    .output = {
        .sorted_ints = CCC_buffer_with_storage(5, (int[5]){-2,-1,0,1,2}),
    },
})

TCG_test_case("random order", {
    .input = {
        .ints = CCC_buffer_with_storage(10,
            (int[10]){8, 1, -34, 22, 4, 19, 12, 88, 93, 2}
        ),
    },
    .output = {
        .sorted_ints = CCC_buffer_with_storage(10,
            (int[10]){-34, 1, 2, 4, 8, 12, 19, 22, 88, 93}
        ),
    },
})

TCG_tests_end(sort_an_array_tests);

#endif /* SORT_AN_ARRAY_TESTS_H */
