#include <stdbool.h>

#include "utility/loggers.h"
#include "utility/test_case_generator.h"

#define BUFFER_USING_NAMESPACE_CCC
#define TRAITS_USING_NAMESPACE_CCC
#define FLAT_PRIORITY_QUEUE_USING_NAMESPACE_CCC
#include "ccc/buffer.h"
#include "ccc/sort.h"
#include "ccc/traits.h"
#include "ccc/types.h"

#include "sort_an_array_tests.h"

static CCC_Order
compare_ints(CCC_Comparator_arguments const arguments) {
    int const *const lhs = arguments.type_left;
    int const *const rhs = arguments.type_right;
    return (*lhs > *rhs) - (*lhs < *rhs);
}

static inline bool
buffers_match(Buffer const *const a, Buffer const *const b) {
    if (count(a).count != count(b).count) {
        return false;
    }
    for (int const *a_int = begin(a), *b_int = begin(b); a_int != end(a);
         a_int = next(a, a_int), b_int = next(b, b_int)) {
        if (*a_int != *b_int) {
            return false;
        }
    }
    return true;
}

static struct Sort_an_array_output
sort_an_array(struct Sort_an_array_input *const input) {
    if (is_empty(&input->ints)) {
        return (struct Sort_an_array_output){};
    }
    CCC_Result const result = CCC_sort_heapsort(
        &input->ints,
        &(int){},
        CCC_ORDER_LESSER,
        &(CCC_Comparator){.compare = compare_ints}
    );
    if (result != CCC_RESULT_OK) {
        return (struct Sort_an_array_output){};
    }
    return (struct Sort_an_array_output){input->ints};
}

int
main(void) {
    int passed = 0;
    TCG_for_each_test_case(sort_an_array_tests, {
        struct Sort_an_array_output const output
            = sort_an_array(&TCG_test_case_input(sort_an_array_tests));
        struct Sort_an_array_output const *const correct_output
            = &TCG_test_case_output(sort_an_array_tests);
        if (!buffers_match(&output.sorted_ints, &correct_output->sorted_ints)) {
            logfail(sort_an_array_tests);
        } else {
            ++passed;
        }
    });
    return TCG_tests_status(sort_an_array_tests, passed);
}
