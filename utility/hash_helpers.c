#include <stdint.h>

#include "ccc/types.h"
#include "hash_helpers.h"

CCC_Order
hash_map_int_key_val_order(CCC_Key_comparator_context const order)
{
    struct Int_key_val const *const right = order.type_right;
    int const left = *((int *)order.key_left);
    return (left > right->key) - (left < right->key);
}

uint64_t
hash_map_int_to_u64(CCC_Key_context const k)
{
    int const id_int = *((int *)k.key);
    uint64_t x = id_int;
    x = (x ^ (x >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
    x = (x ^ (x >> 27)) * UINT64_C(0x94d049bb133111eb);
    x = x ^ (x >> 31);
    return x;
}
