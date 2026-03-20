#include <stddef.h>
#include <stdlib.h>

#include "allocators.h"

#include "ccc/types.h"

void *
stdlib_allocate(CCC_Allocator_arguments const arguments) {
    if (!arguments.input && !arguments.bytes) {
        return NULL;
    }
    if (!arguments.input) {
        return malloc(arguments.bytes);
    }
    if (!arguments.bytes) {
        free(arguments.input);
        return NULL;
    }
    return realloc(arguments.input, arguments.bytes);
}

CCC_Allocator const std_allocator = {.allocate = stdlib_allocate};
