#include "lib.h"

void print_error(char* errorMsg) {
    printf( RED_CL"%s\n" DEFAULT_CL, errorMsg);
}

float simplify(char* index, void* size) {
    unsigned long cap = ((unsigned long) size);
    const int BASE = 1024;
    int base = log(cap) / log(BASE);
    if(index != NULL)
        *index = base;

    return (cap / pow(1024, base));
}

void* getRamCapacity(void) {
    unsigned long pages = sysconf(_SC_PHYS_PAGES);
    unsigned long page_size = sysconf(_SC_PAGE_SIZE);

    return (void*)(pages * page_size);
}