#include "lib.h"

int main(void) {
    char line[MAX_LINE_LENGTH];
    struct utsname sys_info;
    FILE *cpuinfo_file = fopen("/proc/cpuinfo", "r");
    FILE *meminfo_file = fopen("/proc/meminfo", "r");
    //Os & kernel info
    if (uname(&sys_info) == -1) {
        perror("Error");
        return 1;
    }
    if (cpuinfo_file == NULL || meminfo_file == NULL) {
        perror("Error opening system information files");
        return 1;
    }
    printf("Operating System: %s\n", sys_info.sysname);
    printf("Kernel version: %s\n", sys_info.release);
    
    //DE
    char *envVarValue = getenv("XDG_CURRENT_DESKTOP");
    if (envVarValue == NULL) {
        printf("Desktop environment not found\n");
        return 1;
    }
    printf("DE: %s\n", envVarValue);
    
    //gpu
    //TODO

    // Print the model of the GPU
    printf("GPU model: %s\n", model);

    // Close the file stream
    pclose(fp);

    //hostname
    char hostname[256];
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        printf("Failed to get hostname\n");
        return 1;
    }
    printf("Hostname: %s\n", hostname);

   //shell
   char* shell = getenv("SHELL");
    printf("Current shell: %s\n", shell);

   //cpuinfo
    while (fgets(line, MAX_LINE_LENGTH, cpuinfo_file) != NULL) {
        if (strstr(line, "model name") != NULL) {
            printf("CPU: %s", line + strlen("model name")+3);
            break;
        }
    }
    //raminfo
    while (fgets(line, MAX_LINE_LENGTH, meminfo_file) != NULL) {
        if (strstr(line, "MemTotal") != NULL) {
            printf("RAM: %s", line  + strlen("MemTotal:") +8) ;
            break;
        }
    }
    //uptimeinfo
    printf("Uptime: ");
    fflush(stdout);
    system("uptime -p");
    fclose(cpuinfo_file);
    fclose(meminfo_file);
    struct statvfs fs_info;
    const char *path = "/"; 

    if (statvfs(path, &fs_info) != 0) {
        perror("Error calling statvfs");
        return 1;
    }

    // disk usage
    unsigned long long block_size = fs_info.f_frsize; 
    unsigned long long total_blocks = fs_info.f_blocks;
    unsigned long long free_blocks = fs_info.f_bfree; 
    unsigned long long total_size = block_size * total_blocks / (1024.0 * 1024.0 * 1024.0);
    unsigned long long free_size = block_size * free_blocks / (1024.0 * 1024.0 * 1024.0); 

    printf("Disk usage: %llu / %llu Gb\n", total_size, free_size);
    return 0;
}

