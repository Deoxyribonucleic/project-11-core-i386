#ifndef _STDIO_H_
#define _STDIO_H_

#define BUFSIZ 1024

#define stdin 0
#define stdout 1
#define stderr 2

void printf(char *fmt, ...);
void fprintf(int fd, char *fmt, ...);

#endif

