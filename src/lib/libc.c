/*
 * * libc.c
 * * functions from the standard C library that are needed by the Lua 5.1 core
 * * Luiz Henrique de Figueiredo <lhf@tecgraf.puc-rio.br>
 * * 08 Nov 2007 09:24:22
 * * This code is hereby placed in the public domain.
 * */

#include <string.h>

int errno = 0;

size_t strlen(const char *s)
{
	 size_t n=0;
	  while (*s++) n++;
	   return n;
}

char *strchr(const char *s, int c)
{
	 while (*s!=c && *s!=0) s++;
	  return (*s==c) ? (char*)s : NULL;
}

char *strcpy(char *d, const char *s)
{
	 char *t=d;
	  while ((*t++=*s++)) ;
	   return d;
}

char *strncpy(char *d, const char *s, size_t n)
{
	 char *t=d;
	  while (n-- && (*t++=*s++)) ;
#if 0
	   if (n+1) while (n--) *t++='-';
#endif
	   return d;
}

char *strcat(char *d, const char *s)
{
	 return strcpy(d+strlen(d),s);
}

char *strncat(char *d, const char *s, size_t n)
{
	 return strncpy(d+strlen(d),s,n);
}

int strcmp(const char *s1, const char *s2)
{
	 const unsigned char *a=s1;
	  const unsigned char *b=s2;
	   while (*a==*b && *a!=0 && *b!=0) a++,b++;
	    return *a-*b;
}

int strncmp(const char *cs, const char *ct, size_t count)
{
	unsigned char c1, c2;

	while (count) {
		c1 = *cs++;
		c2 = *ct++;
		if (c1 != c2)
			return c1 < c2 ? -1 : 1;
		if (!c1)
			break;
		count--;
	}
	return 0;
}

int strcoll(const char *s1, const char *s2)
{
	 return strcmp(s1,s2);
}

size_t strcspn(const char *s, const char *reject)
{
	 size_t n=0;
	  for (n=0; *s; n++,s++)
		   {
			     const char *r;
				   for (r=reject; *r; r++) if (*r==*s) return n;
				    }
	   return n;
}

void *memcpy(void *d, const void *s, size_t n)
{
	 char *a=d;
	  const char *b=s;
	   while (n--) *a++=*b++;
	    return d;
}

int memcmp(const void *s1, const void *s2, size_t n)
{
	 const unsigned char *a=s1;
	  const unsigned char *b=s2;
	   if (n==0) return 0;
	    while (--n && *a==*b) a++,b++;
		 return *a-*b;
}

#include <math.h>

double floor(double x)
{
	 return (double)(int)x;
}

int abs(int x)
{
	 return (x>=0) ? x : -x;
}

#include <ctype.h>

int (isalpha)(int c)
{
	 return (c>='A' && c<='Z') || (c>='a' && c<='z');
}

int (isalnum)(int c)
{
	 return (c>='A' && c<='Z') || (c>='a' && c<='z') || (c>='0' && c<='9');
}

int (isdigit)(int c)
{
	 return (c>='0' && c<='9');
}

int (isspace)(int c)
{
	 return (c==' ' || c=='\t' || c=='\n' || c=='\r' || c=='\f' || c=='\v');

}

int (iscntrl)(int c)
{
	 return (c>=0 && c<' ') || c==127;
}

char* strerror(int err)
{
	return "strerror not implemented";
}

char *strstr(const char *s1, const char *s2)
{
	size_t l1, l2;

	l2 = strlen(s2);
	if (!l2)
		return (char *)s1;
	l1 = strlen(s1);
	while (l1 >= l2) {
		l1--;
		if (!memcmp(s1, s2, l2))
			return (char *)s1;
		s1++;
	}
	return NULL;
}

void *memmove( void *destination, const void *source, size_t num)
{
	if(destination == source)
		return destination;

	if(source > destination)
	{
		size_t i;
		for(i=0; i<num; ++i)
			((char*)destination)[i] = ((char*)source)[i];
		return destination;
	}

	size_t i;
	for(i=num; i>0; --i)
		((char*)destination)[i - 1] = ((char*)source)[i - 1];
	return destination;
}


#include <stdlib.h>

void* malloc(size_t size)
{
	return mem_alloc(size);
}

void* realloc(void* ptr, size_t size)
{
	return mem_realloc(ptr, size);
}

void free(void* ptr)
{
	mem_free(ptr);
}


#include <stdio.h>

void fflush(FILE* file)
{
}

