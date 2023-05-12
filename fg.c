#include "fg.h"

int fg_command(char* tokenS, int* jobArray) {

    tokenS = strtok(NULL, " ");

    if (tokenS != NULL) {

        int job = atoi(tokenS);
        int pid = jobArray[job];

        int status;
        setpgid(pid, getpgid(0));

        signal(SIGTTIN, SIG_IGN);
        signal(SIGTTOU, SIG_IGN);

        tcsetpgrp(0, pid);

        if (kill(pid, SIGCONT) < 0) perror("Error");

        waitpid(pid, &status, WUNTRACED);

        tcsetpgrp(0, getpgid(0));

        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);

        if (WIFSTOPPED(status)) {
            setpgid(pid, pid);
            return 0;
        }

        return WIFEXITED(status) ? pid : -pid;

    } else {

        printf("Error: Too few arguments.\n");

    }
        



}