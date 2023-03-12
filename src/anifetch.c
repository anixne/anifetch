#include "lib.h"

int main(void) {
    char* line = (char*) calloc(MAX_LINE_LENGTH, sizeof(char));
    struct utsname sys_info;
    FILE *cpuinfo_file = fopen("/proc/cpuinfo", "r");
    FILE *meminfo_file = fopen("/proc/meminfo", "r");
    //Os & kernel info
    if (uname(&sys_info) == -1) {
        print_error("Error");
        return 1;
    }
    if (cpuinfo_file == NULL || meminfo_file == NULL) {
        print_error("Error opening system information files");
        return 1;
    }
    printf(GREEN_CL "Operating System: %s\n" DEFAULT_CL, sys_info.sysname);
    printf(YELLOW_CL "Kernel version: %s\n" DEFAULT_CL, sys_info.release);
    
    //hostname
    char* hostname = (char*) calloc(MAX_LINE_LENGTH, sizeof(char));
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        print_error("Failed to get hostname");
        return 1;
    }
    printf(BLUE_CL "Hostname: %s\n" DEFAULT_CL, hostname);
    free(hostname); //hostname releasing

   //shell
   char* shell = getenv("SHELL");
    printf(PURPLE_CL "Current shell: %s\n" DEFAULT_CL, shell);

   //cpuinfo
    while (fgets(line, MAX_LINE_LENGTH, cpuinfo_file) != NULL) {
        if (strstr(line, "model name") != NULL) {
            printf(GREEN_CL "CPU: %s" DEFAULT_CL, line + strlen("model name")+3);
            break;
        }
    }
    //raminfo
    while (fgets(line, MAX_LINE_LENGTH, meminfo_file) != NULL) {
        if (strstr(line, "MemTotal") != NULL) {
            printf(CYAN_CL "RAM: %s" DEFAULT_CL, line + strlen("MemTotal:") +8);
            break;
        }
    }
    free(line); //releasing line

    //uptimeinfo
    printf(YELLOW_CL "Uptime: ");
    fflush(stdout);
    system("uptime -p");
    printf(DEFAULT_CL);
    fclose(cpuinfo_file);
    fclose(meminfo_file);
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
    unsigned long long total_size = block_size * total_blocks / (1024.0 * 1024.0 * 1024.0);
    unsigned long long free_size = block_size * free_blocks / (1024.0 * 1024.0 * 1024.0);
    //TODO: automatic scale measure

    printf(WHITE_CL "Disk usage: %llu / %llu Gb\n" DEFAULT_CL, total_size, free_size);
    return 0;
}
