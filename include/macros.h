#ifndef _MACROS_H_
#define _MACROS_H_

#define true 1
#define false 0

// Avoid compiler warnings for unused variables
#ifdef __GNUC__
#define UNUSED __attribute__((unused))
#else
#define UNUSED
#endif

#endif
