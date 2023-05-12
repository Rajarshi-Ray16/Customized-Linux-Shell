#include "echo.h"

void echo_command(char* tokenS, int times, int flag) {

    char stringToBePrinted[512] = "";

    if (flag == 0) {
        while (tokenS != NULL) {
            tokenS = strtok(NULL, " ");
            if (tokenS != NULL) {
                strcat(stringToBePrinted, tokenS);
                strcat(stringToBePrinted, " ");
            }
        }
        for (int i = 0; i < times; i++) {
            printf("%s\n", stringToBePrinted);
        }
    } else {
        char* sign = ">";
        while (tokenS != NULL) {

            tokenS = strtok(NULL, " ");

            if (strcmp(tokenS, sign) == 0) {
                
                tokenS = strtok(NULL, " ");
                    
                //Current file pointer
                FILE *fptr;
                //Storing the current working directory.
                char storeCWD[512];
                getcwd(storeCWD, 512);
                strcat(storeCWD, "/");
                strcat(storeCWD, tokenS);

                fptr = fopen(storeCWD, "w");

                if (fptr == NULL) {
                    printf("Error!");   
                    exit(1);             
                }
                
                for (int i = 0; i < times; i++) {
                    fprintf(fptr, "%s\n", stringToBePrinted);
                }
                fclose(fptr);

                break;

            } else {
                strcat(stringToBePrinted, tokenS);
                strcat(stringToBePrinted, " ");
            } 

        }
    }                    
}