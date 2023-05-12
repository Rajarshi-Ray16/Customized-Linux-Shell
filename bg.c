#include "bg.h"

int bg_command(char* tokenS, int* jobArray) {

    tokenS = strtok(NULL, " ");

    if (tokenS != NULL) {

        int job = atoi(tokenS);
        int pid = jobArray[job];

        if (kill(pid, SIGCONT) < 0) {

            perror("Error");
            return -1;

        }

    } else {

        printf("Error: Too few arguments.\n");

    }

    return 0;

}