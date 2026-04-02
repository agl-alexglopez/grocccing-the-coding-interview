#ifndef GROUP_ANAGRAMS_TESTS_H
#define GROUP_ANAGRAMS_TESTS_H

#include "utility/test_case_generator.h"

#include "ccc/flat_buffer.h"
#include "str_view/str_view.h"

/** The input strings to the problem. */
struct Group_anagrams_input {
    /** A buffer of SV_Str_view strings. */
    CCC_Flat_buffer strs;
};

/** The output buffer of buffer anagram SV_Str_view groups. */
struct Group_anagrams_output {
    /** A buffer of buffers. Each buffer groups the string view anagrams. */
    CCC_Flat_buffer flat_buffer_of_groups;
};

TCG_tests_begin(group_anagrams_tests,
                struct Group_anagrams_input,
                struct Group_anagrams_output)
TCG_test_case("3 groups", {
    .input = {
        .strs = CCC_flat_buffer_with_storage(
            6,
            (SV_Str_view[6]){
                SV_from("eat"),
                SV_from("tea"),
                SV_from("tan"),
                SV_from("ate"),
                SV_from("nat"),
                SV_from("bat"),
            }
        ),
    },
    .output = {
        .flat_buffer_of_groups = CCC_flat_buffer_with_storage(
            3,
            (CCC_Flat_buffer[3]){
                CCC_flat_buffer_with_storage(
                    3,
                    (SV_Str_view[3]){
                        SV_from("ate"),
                        SV_from("eat"),
                        SV_from("tea"),
                    }
                ),
                CCC_flat_buffer_with_storage(
                    2,
                    (SV_Str_view[2]){
                        SV_from("nat"),
                        SV_from("tan"),
                    }
                ),
                CCC_flat_buffer_with_storage(
                    1,
                    (SV_Str_view[1]){
                        SV_from("bat"),
                    }
                ),
            }
        )
    },
})
TCG_test_case("all identical", {
    .input = {
        .strs = CCC_flat_buffer_with_storage(
            5,
            (SV_Str_view[5]){
                SV_from("aa"),
                SV_from("aa"),
                SV_from("aa"),
                SV_from("aa"),
                SV_from("aa"),
            }
        ),
    },
    .output = {
        .flat_buffer_of_groups = CCC_flat_buffer_with_storage(
            1,
            (CCC_Flat_buffer[1]){
                CCC_flat_buffer_with_storage(
                    5,
                    (SV_Str_view[5]){
                        SV_from("aa"),
                        SV_from("aa"),
                        SV_from("aa"),
                        SV_from("aa"),
                        SV_from("aa"),
                    }
                ),
            }
        ),
    },
})
TCG_test_case("no anagrams", {
    .input = {
        .strs = CCC_flat_buffer_with_storage(
            3,
            (SV_Str_view[3]){
                SV_from("abc"),
                SV_from("def"),
                SV_from("ghi"),
            }
        ),
    },
    .output = {
        .flat_buffer_of_groups = CCC_flat_buffer_with_storage(
            3,
            (CCC_Flat_buffer[3]){
                CCC_flat_buffer_with_storage(
                    1, (SV_Str_view[1]){ SV_from("abc") }
                ),
                CCC_flat_buffer_with_storage(
                    1, (SV_Str_view[1]){ SV_from("def") }
                ),
                CCC_flat_buffer_with_storage(
                    1, (SV_Str_view[1]){ SV_from("ghi") }
                ),
            }
        )
    },
})
TCG_test_case("empty input", {
    .input = {
        .strs = CCC_flat_buffer_default(SV_Str_view),
    },
    .output = {
        .flat_buffer_of_groups = CCC_flat_buffer_default(CCC_Flat_buffer),
    },
})
TCG_test_case("single string", {
    .input = {
        .strs = CCC_flat_buffer_with_storage(
            1,
            (SV_Str_view[1]){
                SV_from("solo"),
            }
        ),
    },
    .output = {
        .flat_buffer_of_groups = CCC_flat_buffer_with_storage(
            1,
            (CCC_Flat_buffer[1]){
                CCC_flat_buffer_with_storage(
                    1,
                    (SV_Str_view[1]){ SV_from("solo") }
                ),
            }
        ),
    },
})
TCG_test_case("mixed length anagrams", {
    .input = {
        .strs = CCC_flat_buffer_with_storage(
            7,
            (SV_Str_view[7]){
                SV_from("abcd"),
                SV_from("bcad"),
                SV_from("dabc"),
                SV_from("abc"),
                SV_from("cab"),
                SV_from("bac"),
                SV_from("zzz")
            }
        ),
    },
    .output = {
        .flat_buffer_of_groups = CCC_flat_buffer_with_storage(
            3,
            (CCC_Flat_buffer[3]){
                CCC_flat_buffer_with_storage(
                    3,
                    (SV_Str_view[3]){
                        SV_from("abcd"),
                        SV_from("bcad"),
                        SV_from("dabc"),
                    }
                ),
                CCC_flat_buffer_with_storage(
                    3,
                    (SV_Str_view[3]){
                        SV_from("abc"),
                        SV_from("bac"),
                        SV_from("cab"),
                    }
                ),
                CCC_flat_buffer_with_storage(
                    1,
                    (SV_Str_view[1]){
                        SV_from("zzz"),
                    }
                ),
            }
        ),
    },
})
TCG_tests_end(group_anagrams_tests);

#endif /* GROUP_ANAGRAMS_TESTS_H */
