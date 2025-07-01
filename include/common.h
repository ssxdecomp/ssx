#ifndef COMMON_H
#define COMMON_H

// Just include the Splat header for now.
#include "include_asm.h"

typedef unsigned char u8;
typedef signed char   i8;
typedef unsigned short u16;
typedef signed short   i16;
typedef unsigned int u32;
typedef signed int   i32;
typedef unsigned long long u64;
typedef signed long long i64;

typedef __typeof__(sizeof(0)) usize; // NOLINT


#define arraysize(arr) (sizeof(arr)/sizeof(arr[0]))

#endif