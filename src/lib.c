#include "lib.h"

#define MAX_GPU_LINE 256

void print_error(char *errorMsg) { printf(RED_CL "%s\n" DEFAULT_CL, errorMsg); }

float simplify(char *index, void *size) {
  unsigned long cap = ((unsigned long)size);
  const int BASE = 1024;
  int base = log(cap) / log(BASE);
  if (index != NULL)
    *index = base;

  return (cap / pow(1024, base));
}

void *getRamCapacity(void) {
  unsigned long pages = sysconf(_SC_PHYS_PAGES);
  unsigned long page_size = sysconf(_SC_PAGE_SIZE);

  return (void *)(pages * page_size);
}

void printGpuInfo() {
  FILE* fp = popen("lspci -kv | grep -Ei \"(3D|VGA)\"", "r");
  char* line = (char*) malloc(MAX_GPU_LINE);
  char* init = line;
  printf(GREEN_CL);
  while(fgets(line, MAX_GPU_LINE, fp)) {
    line = trim(line);
    line = subtr(line);
    printf("GPU: %s", line);
  }
  printf(DEFAULT_CL);
  line = init;
  free(line);
}

char* trim(char* s) {
  char* back = s + strlen(s);
  while(isspace(*--back));
  *(back+1) = '\0';
  s = ltrim(s);
  return s;
}

char* ltrim(char* s) {
  while(isspace(*s)) s++;
  return s;
}

char* subtr(char* s) {
  subfr(s);
  uint8_t second = 0;
  while(*s) {
    if(*s == ':') {
      second++;
      if(second == 2) {
        return (s+1);
      }
    }
    s++;
  }
  return NULL;
}

void subfr(char* s){
  while(*s) {
    if(*s == '(') {
      *s = '\n';
      *(s+1) = '\0';
      return;
    }
    s++;
  }
}