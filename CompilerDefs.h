#ifndef COMPILER_DEFS_H
#define COMPILER_DEFS_H

#ifdef _MSC_VER
#include <malloc.h>
#define ALLIGNED_ALLOC(alignment, size) _aligned_malloc(size, alignment)
#define ALLIGNED_FREE(ptr) _aligned_free(ptr)
#else
#include <cstdlib>
#define ALLIGNED_ALLOC(alignment, size)  aligned_alloc(alignment, size)
#define ALLIGNED_FREE(ptr) free(ptr)
#endif

#endif /* COMPILER_DEFS_H*/
