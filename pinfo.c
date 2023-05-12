#include "pinfo.h"

void pinfo_command(char* tokenS) {
    
    pid_t currentP;

    tokenS = strtok(NULL, " ");

    if (tokenS == NULL) {
         currentP = getpid();
    } else {
         currentP = atoi(tokenS);
    } 

    char* pathP = calloc(1024, sizeof(char));
    sprintf(pathP, "%d", currentP);

    int length1 = strlen(pathP) + strlen("/proc/") * strlen("/status") + 1;
    char* path_name1 = calloc(length1, sizeof(char));

    strcat(path_name1, "/proc/");
    strcat(path_name1, pathP);
    strcat(path_name1, "/status");

    FILE* current_file1;
    current_file1 = fopen(path_name1, "r");

    char* state_string1 = calloc(100, sizeof(char));

    for (int counter = 0; fgets(state_string1, 100, current_file1) != NULL; counter++) {

        if (counter == 1) {
            break;
        }
            
    }

    fclose(current_file1);
    free(path_name1);

    int length2 = strlen(pathP) + strlen("/proc/") * strlen("/statm") + 1;
    char* path_name2 = calloc(length2, sizeof(char));

    strcat(path_name2, "/proc/");
    strcat(path_name2, pathP);
    strcat(path_name2, "/statm");

    FILE* current_file2;
    current_file2 = fopen(path_name2, "r");

    char* memory_string = calloc(50, sizeof(char));
    fscanf(current_file2, "%s", memory_string);

    fclose(current_file2);
    free(path_name2);                    
    
    int length3 = strlen(pathP) + strlen("/proc/") + strlen("/exe") + 1;
    char* current_path = calloc(length3, sizeof(char));
    strcat(current_path, "/proc/");
    strcat(current_path, pathP);
    strcat(current_path, "/exe");
    char* state_string2 = calloc(100, sizeof(char));
    readlink(current_path, state_string2, 100);

    free(current_path);

    printf("pid: %s\n%sMemory: %s\nExecutable Path: %s\n", pathP, state_string1, memory_string, state_string2);

    free(pathP);
    free(state_string1);
    free(memory_string);
    free(state_string2);
}