#ifndef ALLOCATORS_H
#define ALLOCATORS_H

#include "ccc/types.h"

void *stdlib_allocate(CCC_Allocator_arguments);

extern CCC_Allocator const std_allocator;

#endif /* ALLOCATORS_H */
