#include "sig.h"

int sig_command(char* tokenS, int* jobArray) {

    tokenS = strtok(NULL, " ");

    if (tokenS != NULL) {

        int job = atoi(tokenS);
        tokenS = strtok(NULL, " ");
        
        if ((tokenS != NULL) && !(job < 1 || job > 99 || jobArray[job] <= 1)) {

            int sig = atoi(tokenS);

            if (kill(jobArray[job], sig) < 0) {

                perror("Error");
                return -1;

            }

        } else if (job < 1 || job > 99 || jobArray[job] <= 1) {

            printf("Error: Invalid Job\n");

        } else {

            printf("Error: Too few arguments\n");

        }

    } else {

        printf("Error: Too few arguments\n");

    }

    return 0;

}