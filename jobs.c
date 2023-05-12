#include "jobs.h"

int jobs_command(int* jobArray, char** bgCommand) {
    
    char filename[1024];
    char status;
    int retValue = 0;

    for (int i = 1; i < 100; i++) {
        
        if (!jobArray[i]) continue;

        snprintf(filename, 1024, "/proc/%d/stat", jobArray[i]);

        FILE* file = fopen(filename, "r");

        if (file) {
            fscanf(file, "%*d %*s %c", &status);
            if (status == 'T') {
                printf("[%d] %s %s [%d]\n", i, "Stopped", bgCommand[i], jobArray[i]);
            } else {
                printf("[%d] %s %s [%d]\n", i, "Running", bgCommand[i], jobArray[i]);
            }
        } else {
            perror("Error");
            return -1;
        }

        fclose(file);
    }

    return 0;
}