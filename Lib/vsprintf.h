#ifndef __VSPRINTF_H
#define __VSPRINTF_H
#include <stdarg.h>
#include "ctype.h"
unsigned long simple_strtoul(const char *cp,char **endp,unsigned int base);
long simple_strtol(const char *cp,char **endp,unsigned int base);
int strnlen(const char * s, int count);
static int skip_atoi(const char **s);
int do_div (long *n,int base);
static char * number(char * str, long long num, int base, int size, int precision ,int type);
int VsPrintf(char *buf, const char *fmt, va_list args);
#endif