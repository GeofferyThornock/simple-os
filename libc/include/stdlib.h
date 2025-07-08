#ifndef _STDLIB_H
#define _STDLIB_H 1
#define bool int
#define false 0
#define true 1

#include <sys/cdefs.h>

#ifdef __cplusplus
extern "C" {
#endif

__attribute__((__noreturn__))
void abort(void);

#ifdef __cplusplus
}
#endif

#endif
