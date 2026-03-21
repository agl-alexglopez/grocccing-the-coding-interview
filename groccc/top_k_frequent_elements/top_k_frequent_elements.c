#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define BUFFER_USING_NAMESPACE_CCC
#define TRAITS_USING_NAMESPACE_CCC
#define FLAT_HASH_MAP_USING_NAMESPACE_CCC
#define PRIORITY_QUEUE_USING_NAMESPACE_CCC
#include "ccc/buffer.h"
#include "ccc/flat_hash_map.h"
#include "ccc/traits.h"
#include "ccc/types.h"

#include "utility/allocators.h"
#include "utility/defer.h"
#include "utility/hash_helpers.h"
#include "utility/loggers.h"
#include "utility/test_case_generator.h"

#include "top_k_frequent_elements_tests.h"

struct Priority_int {
    Priority_queue_node node;
    struct Int_key_val kv;
};

static inline bool
has_num(Buffer const *const b, int const i) {
    for (int const *num = begin(b); num != end(b); num = next(b, num)) {
        if (*num == i) {
            return true;
        }
    }
    return false;
}

static inline bool
are_equal(Buffer const *const a, Buffer const *const b) {
    if (count(a).count != count(b).count) {
        return false;
    }
    if (!count(a).count) {
        return true;
    }
    if (memcmp(begin(a), begin(b), buffer_count_bytes(a).count) == 0) {
        return true;
    }
    for (int const *i = begin(a); i != end(a); i = next(a, i)) {
        if (!has_num(b, *i)) {
            return false;
        }
    }
    return true;
}

static CCC_Order
compare_heap_elements(CCC_Comparator_arguments const context) {
    struct Priority_int const *const lhs = context.type_left;
    struct Priority_int const *const rhs = context.type_right;
    assert(lhs);
    assert(rhs);
    return (lhs->kv.val > rhs->kv.val) - (lhs->kv.val < rhs->kv.val);
}

static void
increase_priority(CCC_Arguments const arguments) {
    struct Priority_int *const p = arguments.type;
    ++p->kv.val;
}

/** I like the heap sort method because it is fast, uses very little space,
and tests more of the Collection data structures. Bucket sort technically meets
the runtime specification but so what. */
static struct Top_k_frequent_elements_output
top_k_frequent_elements(
    struct Top_k_frequent_elements_input const *const input,
    Buffer *const top_k,
    Flat_hash_map *const frequency,
    CCC_Allocator const *const allocator
) {
    reserve(frequency, count(&input->nums).count, allocator);
    /* No cleanup is needed for the priority queue. It lives in the map. */
    Priority_queue max_heap = priority_queue_default(
        struct Priority_int,
        node,
        CCC_ORDER_GREATER,
        (CCC_Comparator){.compare = compare_heap_elements}
    );
    for (int const *i = begin(&input->nums); i != end(&input->nums);
         i = next(&input->nums, i)) {
        struct Priority_int *const entry = flat_hash_map_or_insert_with(
            flat_hash_map_and_modify_with(
                flat_hash_map_entry_wrap(frequency, i, &(CCC_Allocator){}),
                struct Priority_int,
                {
                    priority_queue_update(
                        &max_heap,
                        &T->node,
                        &(CCC_Modifier){.modify = increase_priority}
                    );
                }
            ),
            (struct Priority_int){.kv = {.key = *i, .val = 1}}
        );
        if (entry->kv.val == 1) {
            (void)push(&max_heap, &entry->node, &(CCC_Allocator){});
        }
    }
    if (count(frequency).count < (size_t)input->k) {
        return (struct Top_k_frequent_elements_output){};
    }
    int to_push = input->k;
    while (to_push && !is_empty(&max_heap)) {
        struct Priority_int const *const max = front(&max_heap);
        (void)push_back(top_k, &max->kv.key, allocator);
        pop(&max_heap, &(CCC_Allocator){});
        --to_push;
    }
    return (struct Top_k_frequent_elements_output){*top_k};
}

int
main(void) {
    TCG_Count passed = 0;
    Flat_hash_map frequency_scratch_map = CCC_flat_hash_map_default(
        struct Priority_int,
        kv.key,
        (CCC_Hasher){
            .hash = hash_map_int_to_u64,
            .compare = hash_map_int_key_val_order,
        }
    );
    Buffer top_k_scratch_buffer = buffer_default(int);
    defer {
        clear_and_free(
            &top_k_scratch_buffer, &(CCC_Destructor){}, &std_allocator
        );
        clear_and_free(
            &frequency_scratch_map, &(CCC_Destructor){}, &std_allocator
        );
    }
    TCG_for_each_test_case(top_k_frequent_elements_tests, {
        struct Top_k_frequent_elements_output const output
            = top_k_frequent_elements(
                &TCG_test_case_input(top_k_frequent_elements_tests),
                &top_k_scratch_buffer,
                &frequency_scratch_map,
                &std_allocator
            );
        struct Top_k_frequent_elements_output const *const correct_output
            = &TCG_test_case_output(top_k_frequent_elements_tests);
        if (!are_equal(&output.top_k, &correct_output->top_k)) {
            logfail(top_k_frequent_elements_tests);
        } else {
            ++passed;
        }
        clear(&top_k_scratch_buffer, &(CCC_Destructor){});
        clear(&frequency_scratch_map, &(CCC_Destructor){});
    });
    return TCG_tests_status(top_k_frequent_elements_tests, passed);
}
