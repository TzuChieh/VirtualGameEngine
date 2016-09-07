#pragma once

/**
 * If ENVIRONMENT64 is defined, that means the code is being compiled in 64-bit
 * mode; otherwise, ENVIRONMENT32 is defined for 32-bit mode.
 */

// Visual Studio Compiler Pre-definitions
#if _WIN32 || _WIN64
	#if _WIN64
		#define ENVIRONMENT64
	#else
		#define ENVIRONMENT32
	#endif
#endif

// GNU Compiler Pre-definitions
#if __GNUC__
	#if __x86_64__ || __ppc64__
		#define ENVIRONMENT64
	#else
		#define ENVIRONMENT32
	#endif
#endif

// if the compiler is unrecognizable, assuming it's in 64-bit mode
#if !(_WIN32 || _WIN64 || __GNUC__)
	#define ENVIRONMENT64
#endif

#include <cstdint>

#ifdef ENVIRONMENT64
	typedef char           int8;
	typedef unsigned char  uint8;
	typedef int            int32;
	typedef unsigned int   uint32;
	typedef int64_t        int64;
	typedef uint64_t       uint64;
	typedef float          float32;
	typedef double         float64;
#else
	typedef char           int8;
	typedef unsigned char  uint8;
	typedef int            int32;
	typedef unsigned int   uint32;
	typedef int64_t        int64;
	typedef uint64_t       uint64;
	typedef float          float32;
	typedef double         float64;
#endif

#define VGE_TRUE  1
#define VGE_FALSE 0
