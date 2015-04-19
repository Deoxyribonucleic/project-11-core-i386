#ifndef _SETJMP_H_
#define _SETJMP_H_

#include <stdint.h>
#include "archsetjmp_32.h"

extern int setjmp(jmp_buf b);
extern void longjmp(jmp_buf b, int value);

#endif

