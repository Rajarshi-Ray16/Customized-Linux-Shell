#include "processes.h"

int processes_command(char* tokenX) {
  
    int pid = fork();
    int flag = 0;

    if (tokenX[strlen(tokenX) - 1] == '&') {

        flag = 1;
        
    }

    char** args;

    char* tokenS = strtok(tokenX, " ");
    int i = 0;
   
    while (tokenS != NULL) {

        args[i] = tokenS;
        tokenS = strtok(NULL, " ");
        i++;

    }
    args[i] = NULL;

    if (pid < 0) {

        perror("Error");
        return -1;

    } else if (pid) { //Parent - Must have waitpid

        if (flag) { 

            //This is the case for a background process.
            //Runs only when there is an & in the command.
            //The return is over here, because there is no need to run child process in a bg process.

            fprintf(stderr, "%s started with PID %d\n", args[0], pid);
            return pid;
            
        } else { //Parent - Must have waitpid
                
            int status;

            printf("\n");

            //Happens in case of a foreground process.
            //Ignores any signal from the bg process ie. the custom shell.
            //Both in terms of input and output. 
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU, SIG_IGN);

            tcsetpgrp(0, pid);

            //We want the child process to run.
            //The return value is stored in 'status'.
            //The WUNTRACED gives the signal to the child process that nothing's gonna happen
            //while the child is running.
            //Not applicable here, but had SIGSTOP been applied, then, also, the parent would
            //return rather than just be idle.
            waitpid(pid, &status, WUNTRACED); 

            tcsetpgrp(0, getpid());
            
            //The signal handling returns to default ie. starts taking input and output again.
            signal(SIGTTIN, SIG_DFL);
            signal(SIGTTOU, SIG_DFL);

            //The returns aren't an issue, because even though there is code after this,
            //The parent is waiting for the child process to be done, and reach its own 'return'
            if (WIFSTOPPED(status)) {
                setpgid(pid, pid);
                return pid;
            }

            //This is only if the thing fails.
            if (WEXITSTATUS(status) == EXIT_FAILURE) {
                return -1;
            }

        }

    } else { //Child - Must have execvp 

        signal(SIGTTIN, SIG_DFL);
        signal(SIGTTOU, SIG_DFL);

        setpgid(0, 0);

        // execvp(args[0], args);

        if (execvp(args[0], args) == -1) {
            perror("Error");
            exit(1);
        }

        exit(0);

    }

    return 0;
}