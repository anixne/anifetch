#include "lib.h"
int main(void) {
  char *line = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
  struct utsname sys_info;
  FILE *cpuinfo_file = fopen("/proc/cpuinfo", "r");
  // Os & kernel info
  if (uname(&sys_info) == -1) {
    print_error("Error");
    return 1;
  }
  if (cpuinfo_file == NULL) {
    print_error("Error opening system information files");
    return 1;
  }
  printf(GREEN_CL "Operating System: %s\n" DEFAULT_CL, sys_info.sysname);
  printf(YELLOW_CL "Kernel version: %s\n" DEFAULT_CL, sys_info.release);
   //GPU
  #include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 256

char* get_gpu_info()
{
    FILE* fp;
    char line[MAX_LINE_LENGTH];
    char* model = NULL;

    fp = popen("lspci | grep VGA", "r");
    if (fp == NULL) {
        return strdup("Unknown");
    }

    fgets(line, MAX_LINE_LENGTH, fp);
    model = strstr(line, "VGA compatible controller");
    if (model != NULL) {
        model = strtok(model, ":");
        model = strtok(NULL, ":");
        while (*model == ' ') {
            model++;
        }
        char* end = model + strlen(model) - 1;
        while (*end == '\n' || *end == ' ') {
            *end = '\0';
            end--;
        }
    } else {
        model = "Unknown";
    }
    pclose(fp);

    return strdup(model);
}
    char* gpu_info;
    gpu_info = get_gpu_info();
    printf("GPU: %s\n", gpu_info);
    free(gpu_info);

  
   //DE
    char *envVarValue = getenv("XDG_CURRENT_DESKTOP");
    if (envVarValue == NULL) {
        printf("Desktop environment not found\n");
        return 1;
    }
    printf("DE: %s\n", envVarValue);
  
  // hostname
  char *hostname = (char *)calloc(MAX_LINE_LENGTH, sizeof(char));
  if (gethostname(hostname, sizeof(hostname) * 32) == -1) {
    print_error("Failed to get hostname");
    return 1;
  }
  printf(BLUE_CL "Hostname: %s\n" DEFAULT_CL, hostname);
  free(hostname);

  // shell
  char *shell = getenv("SHELL");
  printf(PURPLE_CL "Current shell: %s\n" DEFAULT_CL, shell);

  // cpuinfo
  uint8_t cores = sysconf(_SC_NPROCESSORS_ONLN);
  while (fgets(line, MAX_LINE_LENGTH, cpuinfo_file) != NULL) {
    if (strstr(line, "model name") != NULL) {
      printf(GREEN_CL "CPU (%d): %s" DEFAULT_CL, cores,
             line + strlen("model name") + 3);
      break;
    }
  }
  free(line);

  // raminfo
  char *units[] = {"B", "KB", "MB", "GB", "TB", "PB"};
  long *ram_capacity = (long *)malloc(sizeof(long));
  float *mem = (float *)malloc(sizeof(float));
  char *unit = (char *)malloc(sizeof(char));

  *ram_capacity = (long)getRamCapacity();
  *mem = simplify(unit, (void *)(*ram_capacity));
  printf(CYAN_CL "RAM: %.1f %s\n" DEFAULT_CL, *mem, units[*unit]);

  free(ram_capacity);
  free(mem);

  // uptimeinfo
  printf(YELLOW_CL "Uptime: ");
  fflush(stdout);
  system("uptime -p");
  printf(DEFAULT_CL);
  fclose(cpuinfo_file);
  struct statvfs fs_info;
  const char *path = "/";

  if (statvfs(path, &fs_info) != 0) {
    print_error("Error calling statvfs");
    return 1;
  }

  // disk usage
  unsigned long long block_size = fs_info.f_frsize;
  unsigned long long total_blocks = fs_info.f_blocks;
  unsigned long long free_blocks = fs_info.f_bfree;
  unsigned long long total_size =
      simplify((void *)0, (void *)(block_size * total_blocks));
  unsigned long long free_size =
      simplify(unit, (void *)(block_size * free_blocks));

  printf(WHITE_CL "Disk usage: %llu / %llu %s\n" DEFAULT_CL, total_size,
         free_size, units[*unit]);

  free(unit);
  return 0;
}
