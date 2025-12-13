#ifndef HASH_HELPERS_H
#define HASH_HELPERS_H

#include <stdint.h>

#include "ccc/types.h"

/*================================  Common Types   ==========================*/

struct Int_key_val
{
    int key;
    int val;
};

/*================================  CCC Callbacks   =========================*/

CCC_Order hash_map_int_key_val_order(CCC_Key_comparator_context order);
uint64_t hash_map_int_to_u64(CCC_Key_context k);

/** @brief A utility hasher for arbitrary hashing and safe aliasing.
@param[in] str key context for which the key field is a pointer to SV_Str_view.
@return the 64 bit hash value for the input bytes.
@note Consider using this for strings or aliasing any data of variable length
and type.
@warning If the underlying data is not null terminated, be sure to set the
correct length for the SV_Str_view.
@note This hasher does not use context.

It is safe to alias any data with this function. The C language specifies that
any type may be safely aliased by `char *` and `char const *`. This hash
function also only iterates over the range provided so it is safe to provide
non-null terminated data to this function (even though the SV_Str_view library
says this is not recommended). */
uint64_t hash_fnv_1a_str_view_to_u64(CCC_Key_context str);

#endif /* HASH_HELPERS_H */
