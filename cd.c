#include "cd.h"

void cd_command(char* tokenS, char* storeCWD, char* home_directory) {

    tokenS = strtok(NULL, " ");
    char location[512];

    if (tokenS == NULL) { 
        getcwd(storeCWD, 512);
        chdir(home_directory);
    } else if (strcmp(tokenS, ".") == 0) {
        char tempDir[512];
        getcwd(tempDir, 512);
        if (strcmp(storeCWD, tempDir) == 0) {
            getcwd(storeCWD, 512);
        }
        //Current Working Directory
        char cwd[512];
        getcwd(cwd, 512);
        printf("%s\n", cwd);
        chdir(cwd);
    } else if ((strcmp(tokenS, "..") == 0) || (strcmp(tokenS, "../") == 0)) {
        getcwd(storeCWD, 512);
        chdir("../");
    } else if (strcmp(tokenS, "~") == 0) {
        getcwd(storeCWD, 512);
        chdir(home_directory);
    } else if (strcmp(tokenS, "-") == 0) {
        char temp[512];
        getcwd(temp, 512);
        chdir(storeCWD);
        strcpy(storeCWD, temp);
    } else {
        getcwd(storeCWD, 512);
        strcpy(location, storeCWD);
        int len = strlen(location);
        strcat(location, "/\0");
        while (tokenS != NULL) {
            strcat(location, tokenS);
            strcat(location, " \0");
            tokenS = strtok(NULL, " ");
        }
        chdir(location);
    }

}  
