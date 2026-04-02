#ifndef TOP_K_FREQUENT_ELEMENTS_TESTS_H
#define TOP_K_FREQUENT_ELEMENTS_TESTS_H

#include "utility/test_case_generator.h"

#include "ccc/flat_buffer.h"

struct Top_k_frequent_elements_input {
    CCC_Flat_buffer nums;
    int k;
};

struct Top_k_frequent_elements_output {
    CCC_Flat_buffer top_k;
};

TCG_tests_begin(top_k_frequent_elements_tests,
                struct Top_k_frequent_elements_input,
                struct Top_k_frequent_elements_output)
TCG_test_case("in order repeats", {
    .input = {
        .nums = CCC_flat_buffer_with_storage(
            6, (int[6]){1,1,1,2,2,3}
        ),
        .k = 2,
    },
    .output = {
        .top_k = CCC_flat_buffer_with_storage(
            2, (int[2]){1,2}
        ),
    },
})
TCG_test_case("mixed repeats", {
    .input = {
        .nums = CCC_flat_buffer_with_storage(
            10, (int[10]){1,2,1,2,1,2,3,1,3,2}
        ),
        .k = 2,
    },
    .output = {
        .top_k = CCC_flat_buffer_with_storage(
            2, (int[2]){1,2}
        ),
    },
})
TCG_tests_end(top_k_frequent_elements_tests);

#endif /* TOP_K_FREQUENT_ELEMENTS_TESTS_H */
