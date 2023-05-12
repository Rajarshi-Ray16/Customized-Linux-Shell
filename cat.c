#include "cat.h"

void cat_command(char* tokenS, int times, int flag) {

    //printf("%d\n", flag);

    if (flag == 1) {
        //printf("Test2\n");
        char* sign = "<";
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

                fptr = fopen(storeCWD, "r");

                if (fptr == NULL) {
                    printf("Error!");   
                    exit(1);             
                }

                for (int i = 0; i < times; i++) {
                    char c = fgetc(fptr);
                    while (c != EOF) {
                        printf ("%c", c);
                        c = fgetc(fptr);
                    }
                }
                
                fclose(fptr);

                break;
            }
        }
    } else if (flag == 4) {
        //printf("Test2\n");
        char* sign = "<";
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

                fptr = fopen(storeCWD, "a");

                if (fptr == NULL) {
                    printf("Error!");   
                    exit(1);             
                }

                for (int i = 0; i < times; i++) {
                    char c = fgetc(fptr);
                    while (c != EOF) {
                        printf ("%c", c);
                        c = fgetc(fptr);
                    }
                }
                
                fclose(fptr);

                break;
            }
        }
    }                    
}
