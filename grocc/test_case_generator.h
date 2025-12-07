#ifndef TCG_TEST_CASE_GENERATOR_H
#define TCG_TEST_CASE_GENERATOR_H

#define TCG_begin_test_cases(test_cases_name, input_type, output_type)         \
    static const struct                                                        \
    {                                                                          \
        char const *const name;                                                \
        input_type input;                                                      \
        output_type output;                                                    \
    }(test_cases_name)[] = {

#define TCG_begin_test_case(string_name, input_type_instance...)               \
    {                                                                          \
        .name = string_name, .input = input_type_instance,

#define TCG_end_test_case(output_type_instance...)                             \
    .output = output_type_instance,                                            \
    }                                                                          \
    ,

#define TCG_end_test_cases(test_cases_name)                                    \
    }                                                                          \
    ;                                                                          \
    static const unsigned long long tcg_count_##test_cases_name                \
        = sizeof(test_cases_name) / sizeof((test_cases_name)[0])

/** @brief Retrieves the string name of the current test being processed in
the for each test case macro.
@param[in] test_cases_name the name of the test cases being iterated over.
@return the string name of the current test. */
#define TCG_test_case_name(test_cases_name) test_cases_name[tcg_index].name

/** @brief Retrieves the input object of the current test being
processed in the for each test case macro.
@param[in] test_cases_name the name of the test cases being iterated over.
@return the current test case input struct type.
@note if a reference to this input instance is desired simply take the address
of the return value, as one would in normal array-wise iteration.

```
struct My_input_type const *input = &TCG_test_case_input(my_test_cases);
```

The user can decide if retrieve by copy or reference is preferred. */
#define TCG_test_case_input(test_cases_name) test_cases_name[tcg_index].input

/** @brief Retrieves the output object of the current test being
processed in the for each test case macro.
@param[in] test_cases_name the name of the test cases being iterated over.
@return the current test case output struct type.
@note if a reference to this output instance is desired simply take the address
of the return value, as one would in normal array-wise iteration.

```
struct My_output_type const *output = &TCG_test_case_output(my_test_cases);
```

The user can decide if retrieve by copy or reference is preferred. */
#define TCG_test_case_output(test_cases_name) test_cases_name[tcg_index].output

/** @brief Runs the provided solution, comparison code, and cleanup code over
the user generated test code.
@param[in] test_cases_name the static constant test cases structure.
@param solution_comparison_and_cleanup_code the code needed to run the solution
function with the test case input type as input, compare the function output to
the test case output, and clean up any allocations as needed.
@note Use the provided name, input, and output getter macros to aid in
processing each test case.

This function lets the user problem executable determine what comparison and
test failure looks like. It does not bring in any print or assert dependencies.
Comparing scalars, arrays, and allocations can be tricky so the user can write
the most type correct code in the provided code block. */
#define TCG_for_each_test_case(test_cases_name,                                \
                               solution_comparison_and_cleanup_code...)        \
    (__extension__({                                                           \
        for (unsigned long long tcg_index = 0;                                 \
             tcg_index < tcg_count_##test_cases_name; ++tcg_index)             \
        {                                                                      \
            solution_comparison_and_cleanup_code                               \
        }                                                                      \
    }))

#endif /* TCG_TEST_CASE_GENERATOR_H */
