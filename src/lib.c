#include "lib.h"

void print_error(char* errorMsg) {
    printf( RED_CL"%s\n" DEFAULT_CL, errorMsg);
}

float simplify(char* index, long size) {
    const int BASE = 1024;
    int base = log(size) / log(BASE);
    *index = base;

    return (size / pow(1024, base));
}

long getRamCapacity(void) {
    long pages = sysconf(_SC_PHYS_PAGES);
    long page_size = sysconf(_SC_PAGE_SIZE);

    return (pages * page_size);
}