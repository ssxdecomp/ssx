#ifndef REAL_CORE_MEMORY_H
#define REAL_CORE_MEMORY_H

#include "common.h"

#ifdef __cplusplus
extern "C" {
#endif

enum {
    // Low allocation (allocates from the beginning of the heap)
    MB_LOW = 0x0,
    // High allocation (allocates from the end of the heap)
    MB_HIGH = 0x10,
    MB_LARGEST = 0x20,
    MB_ALIGN = 0x40,
    MB_PERM = 0x80
}

// The default MB_ flags.
extern i32 mbdefault;

/* Allocates some memory. */
void* MEM_alloc(const char* name, u32 length, i32 flags);

/* Frees it. */
void MEM_free(void* ptr);

#ifdef __cplusplus
};
#endif


#endif