#ifndef _STRING_H_
#define _STRING_H_

#include <stddef.h>
#include <stdint.h>

char* itoa(int value, char* str, int base);

size_t strlen(const char *s);
char *strchr(const char *s, int c);
char *strcpy(char *d, const char *s);
char *strncpy(char *d, const char *s, size_t n);
char *strcat(char *d, const char *s);
char *strncat(char *d, const char *s, size_t n);
int strcmp(const char *s1, const char *s2);
int strncmp(const char *s1, const char *s2, size_t n);
int strcoll(const char *s1, const char *s2);
size_t strcspn(const char *s, const char *reject);
void *memcpy(void *d, const void *s, size_t n);
int memcmp(const void *s1, const void *s2, size_t n);

char *strerror(int err);
char *strstr(const char *in, const char *str);

#endif // _STRING_H_

