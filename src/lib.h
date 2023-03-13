#ifndef _ANIFETCH_LIB_H
#define _ANIFETCH_LIB_H

#include <ctype.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/statvfs.h>
#include <sys/utsname.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 256

#define BLACK_CL "\033[0;30m"
#define RED_CL "\033[0;31m"
#define GREEN_CL "\033[1;32m"
#define YELLOW_CL "\033[1;33m"
#define BLUE_CL "\033[1;34m"
#define PURPLE_CL "\033[0;35m"
#define CYAN_CL "\033[0;36m"
#define WHITE_CL "\033[0;37m"
#define DEFAULT_CL "\033[0m"

#ifdef __cplusplus
extern "C" {
#endif

void print_error(char *);
float simplify(char *, void *);
void *getRamCapacity(void);

#ifdef __cplusplus
}
#endif

#endif