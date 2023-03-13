#include "lib.h"

int main(void) {
    char* line = (char*) calloc(MAX_LINE_LENGTH, sizeof(char));
    struct utsname sys_info;
    FILE *cpuinfo_file = fopen("/proc/cpuinfo", "r");
    //Os & kernel info
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
    
    //hostname
    char* hostname = (char*) calloc(MAX_LINE_LENGTH, sizeof(char));
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        print_error("Failed to get hostname");
        return 1;
    }
    printf(BLUE_CL "Hostname: %s\n" DEFAULT_CL, hostname);
    free(hostname);

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
    free(line);
    
    //raminfo
    char* units[] = { "B", "KB", "MB", "GB", "TB", "PB" };
    long* ram_capacity = (long*) malloc(sizeof(long));
    float* mem = (float*) malloc(sizeof(float));
    char* unit = (char*) malloc(sizeof(char));
    
    *ram_capacity = (long) getRamCapacity();
    *mem = simplify(unit, (void*) (*ram_capacity));
    printf(CYAN_CL "RAM: %.1f %s\n" DEFAULT_CL, *mem, units[*unit]);

    free(ram_capacity);
    free(mem);

    //uptimeinfo
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
    unsigned long long total_size = simplify((void*) 0, (void*)(block_size * total_blocks));
    unsigned long long free_size = simplify(unit, (void*)(block_size * free_blocks));

    printf(WHITE_CL "Disk usage: %llu / %llu %s\n" DEFAULT_CL, total_size, free_size, units[*unit]);
    
    free(unit);
    return 0;
}
