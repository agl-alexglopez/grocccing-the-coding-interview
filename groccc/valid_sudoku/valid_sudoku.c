#include <stdbool.h>
#include <stddef.h>

#define FLAT_BITSET_USING_NAMESPACE_CCC

#include "ccc/flat_bitset.h"
#include "ccc/types.h"

#include "utility/loggers.h"
#include "utility/test_case_generator.h"

#include "valid_sudoku_tests.h"

static inline bool
is_valid_box(
    int const board[const 9][9],
    Flat_bitset *const row_check,
    Flat_bitset *const col_check,
    size_t const row_start,
    size_t const col_start
) {
    Flat_bitset box_check = flat_bitset_with_storage(9, (Bit[9]){});
    for (size_t row = row_start; row < row_start + 3; ++row) {
        for (size_t col = col_start; col < col_start + 3; ++col) {
            int const digit = board[row][col] - 1;
            if (digit < 0) {
                continue;
            }
            if (flat_bitset_set(&box_check, digit, CCC_TRUE) == CCC_TRUE) {
                return false;
            }
            if (flat_bitset_set(row_check, (row * 9) + digit, CCC_TRUE)
                == CCC_TRUE) {
                return false;
            }
            if (flat_bitset_set(col_check, (col * 9) + digit, CCC_TRUE)
                == CCC_TRUE) {
                return false;
            }
        }
    }
    return true;
}

static struct Valid_sudoku_output
valid_sudoku(struct Valid_sudoku_input const *const input) {
    Flat_bitset row_check = flat_bitset_with_storage(9 * 9L, (Bit[9 * 9]){});
    Flat_bitset col_check = flat_bitset_with_storage(9 * 9L, (Bit[9 * 9]){});
    for (size_t row = 0; row < 9; row += 3) {
        for (size_t col = 0; col < 9; col += 3) {
            if (!is_valid_box(input->board, &row_check, &col_check, row, col)) {
                return (struct Valid_sudoku_output){
                    .is_valid = false,
                };
            }
        }
    }
    return (struct Valid_sudoku_output){
        .is_valid = true,
    };
}

int
main(void) {
    TCG_Count passed = 0;
    TCG_for_each_test_case(valid_sudoku_tests, {
        struct Valid_sudoku_output const output
            = valid_sudoku(&TCG_test_case_input(valid_sudoku_tests));
        struct Valid_sudoku_output const *const correct_output
            = &TCG_test_case_output(valid_sudoku_tests);
        if (output.is_valid != correct_output->is_valid) {
            logfail(valid_sudoku_tests);
        } else {
            ++passed;
        }
    });
    return TCG_tests_status(valid_sudoku_tests, passed);
}
