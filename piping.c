#include "piping.h"

void piping_command(char* tokenY, int PC) {

    pid_t pid;
    int fd[2];
    char* tokenP = strtok(tokenY, "|");
    //For the execvp command.
    char** args;

    for (int iter = 0; iter < PC; iter++) {

        pipe(fd);
        pid = fork();

        if (pid == 0) {

            //printf("I'm the first child.\n");
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);

            //Since we're piping with '|', we need individual commands to be separated by the space.
            char* tokenS;
            //To place the command into 'args'.
            int i = 0;

            while (tokenS = strtok_r(tokenP, " ", &tokenP)) {
                args[i] = tokenS;
                i++;
            }
            args[i] = NULL;
    
            //printf("Test1\n");
            execvp(args[0], args);

        } else {

            tokenP = strtok(NULL, "|");

            pid = fork();

            if (pid == 0) {

                //printf("I'm the second child.\n");
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]);
                
                //Since we're piping with '|', we need individual commands to be separated by the space.
                char* tokenS;
                //To place the command into 'args'.
                int i = 0;

                while (tokenS = strtok_r(tokenP, " ", &tokenP)) {
                    args[i] = tokenS;
                    i++;
                }
                args[i] = NULL;

                execvp(args[0], args);

            }
        }

    }



}