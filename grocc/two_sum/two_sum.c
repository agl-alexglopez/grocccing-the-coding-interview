#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "ccc/flat_hash_map.h"
#include "ccc/types.h"

#include "../test_case_generator.h"
#include "two_sum_test_cases.h"

struct Val
{
    int key;
    int val;
};

/** A small fixed map is good when 64 is a desirable upper bound on capacity.
Insertions can continue for about 87.5% of the capacity so about 56. Play it
safe and avoid this limit unless testing insertion failure is important. */
CCC_flat_hash_map_declare_fixed_map(Small_fixed_map, struct Val, 64);

static CCC_Order
flat_hash_map_id_order(CCC_Key_comparator_context const order)
{
    struct Val const *const right = order.type_right;
    int const left = *((int *)order.key_left);
    return (left > right->key) - (left < right->key);
}

static uint64_t
flat_hash_map_int_to_u64(CCC_Key_context const k)
{
    int const id_int = *((int *)k.key);
    uint64_t x = id_int;
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x;
}

struct Two_sum_output
two_sum(struct Two_sum_input const *const test_case)
{
    CCC_Flat_hash_map map = CCC_flat_hash_map_initialize(
        &(Small_fixed_map){}, struct Val, key, flat_hash_map_int_to_u64,
        flat_hash_map_id_order, NULL, NULL,
        CCC_flat_hash_map_fixed_capacity(Small_fixed_map));
    struct Two_sum_output solution = {-1, -1};
    for (size_t i = 0; i < test_case->nums_count; ++i)
    {
        struct Val const *const other_addend = CCC_flat_hash_map_get_key_value(
            &map, &(int){test_case->target - test_case->nums[i]});
        if (other_addend)
        {
            solution.addends[0] = (int)i;
            solution.addends[1] = other_addend->val;
        }
        (void)CCC_flat_hash_map_insert_or_assign(&map,
                                                 &(struct Val){
                                                     .key = test_case->nums[i],
                                                     .val = (int)i,
                                                 });
    }
    return solution;
}

int
main(void)
{
    TCG_for_each_test_case(two_sum_tests, {
        struct Two_sum_output const solution_output
            = two_sum(&TCG_test_case_input(two_sum_tests));
        struct Two_sum_output const *const correct_output
            = &TCG_test_case_output(two_sum_tests);
        if ((solution_output.addends[0] != correct_output->addends[0]
             && solution_output.addends[0] != correct_output->addends[1])
            || (solution_output.addends[1] != correct_output->addends[0]
                && solution_output.addends[1] != correct_output->addends[1]))
        {
            (void)fprintf(stderr, "fail case: %s\n",
                          TCG_test_case_name(two_sum_tests));
            return 1;
        }
        (void)fprintf(stderr, "pass case: %s\n",
                      TCG_test_case_name(two_sum_tests));
    });
    return 0;
}
