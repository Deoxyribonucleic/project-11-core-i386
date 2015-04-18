#ifndef _STDIO_H_
#define _STDIO_H_

#include <stdint.h>

#define BUFSIZ 1024


typedef struct
{
	uint8_t dummy;
} FILE;

void printf(char *fmt, ...);
void fprintf(FILE* file, char *fmt, ...);

static const FILE *stdin, *stdout, *stderr;

void fflush(FILE* file);

#endif

