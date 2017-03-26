#ifndef COMPILER_DEFS_H
#define COMPILER_DEFS_H

#ifdef _MSC_VER
#include <malloc.h>
#define ALLIGNED_ALLOC _aligned_malloc
#else
#include <cstdlib>
#define ALLIGNED_ALLOC  aligned_alloc
#endif

#endif /* COMPILER_DEFS_H*/
