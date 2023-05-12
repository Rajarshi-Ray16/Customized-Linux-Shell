#include "cd.h"
#include "echo.h"
#include "pwd.h"
#include "repeat.h"
#include "pinfo.h"
#include "ls.h"
#include "sleep.h"
#include "processes.h"
#include "sign.h"
#include "cat.h"
#include "sort.h"
#include "piping.h"
#include "sig.h"
#include "fg.h"
#include "bg.h"
#include "jobs.h"
#include "headings.h"
// #include "extra.h"

extern int errno;

//Value for the maximum number of bytes in given buffer.
#define MAX_BUF (int)1024

bool fgRunning = false;
int jobArray[100] = {1};
char* bgCommand[100];
int error = 0;

//This adds the bg.
//Takes the pid from somewhere.
void addBg(int pid, char* command) {
    if (!pid) return;

    int pos = 99;

    while (!jobArray[pos]) pos--;

    pos++;

    jobArray[pos] = pid;
    bgCommand[pos] = malloc(strlen(command) + 1);
    strcpy(bgCommand[pos], command);
}

void removeBg(int pid) {
    if (!pid) return;

    for (int i = 1; i < 100; i++) {
        if (jobArray[i] == pid) {
        jobArray[i] = 0;
        free(bgCommand[i]);
        break;
        }
    }
}

void bgHandler() {

    int status;
    int pid = waitpid(-1, &status, WNOHANG);

    if (pid > 0) {
        int pos = 0;
        while (jobArray[pos] != pid) pos++;

        if (WIFSTOPPED(status)) return;

        printf("%s with PID %d exited %s\n", bgCommand[pos], jobArray[pos], WIFEXITED(status) ? "normally" : "abnormally");

        //The variable used to store the current path.
        char path[MAX_BUF];
        //The variable used to store the username of the system.
        char* username;
        //The variable used to store the name of the operating system in use.
        char system[MAX_BUF];
        getcwd(path, MAX_BUF);
        gethostname(system, MAX_BUF);
        // if (strcmp(path, homeDirectory) == 0) {
        //     printf("\033[01;32m%s@%s\033[01;00m:\033[01;34m%s\033[01;00m> ", getenv("USER"), system, "~");
        // } else {
            printf("\033[01;32m%s@%s\033[01;00m:\033[01;34m%s\033[01;00m> ", getenv("USER"), system, path);
        // }

        jobArray[pos] = 0;
        free(bgCommand[pos]);
    }

}

void ctrlCZhandler() {
    if (!fgRunning) {
        printf("\n");
        //The variable used to store the current path.char* homeDirectory
        char path[MAX_BUF];
        //The variable used to store the username of the system.
        char* username;
        //The variable used to store the name of the operating system in use.
        char system[MAX_BUF];
        getcwd(path, MAX_BUF);
        gethostname(system, MAX_BUF);
        // if (strcmp(path, homeDirectory) == 0) {
        //     printf("\033[01;32m%s@%s\033[01;00m:\033[01;34m%s\033[01;00m> ", getenv("USER"), system, "~");
        // } else {
            printf("\033[01;32m%s@%s\033[01;00m:\033[01;34m%s\033[01;00m> ", getenv("USER"), system, path);
        // }
    } else {
        fgRunning = false;
    }
}

int  main() {

    bool run = true;

    //The variable is used to store the current path as the home directory.s
    char homeDirectory[MAX_BUF];
    getcwd(homeDirectory, MAX_BUF);
    
    signal(SIGINT, ctrlCZhandler);
    signal(SIGTSTP, ctrlCZhandler);
    signal(SIGCHLD, bgHandler);

    while (run) {

        //The variable used to store the current path.
        char path[MAX_BUF];
        //The variable used to store the username of the system.
        char* username;
        //The variable used to store the name of the operating system in use.
        char system[MAX_BUF];
        getcwd(path, MAX_BUF);
        gethostname(system, MAX_BUF);
        if (strcmp(path, homeDirectory) == 0) {
            printf("\033[01;32m%s@%s\033[01;00m:\033[01;34m%s\033[01;00m> ", getenv("USER"), system, "~");
        } else {
            printf("\033[01;32m%s@%s\033[01;00m:\033[01;34m%s\033[01;00m> ", getenv("USER"), system, path);
        }
        
        //Original command with spaces and tabs
        char commandOG[100];
        //Final command used to account for extra spaces
        char commandF1[100];

        if (fgets(commandOG, 100, stdin) == NULL) {
            printf("logout\n");
            exit(0);
        }

        commandOG[strcspn(commandOG, "\n")] = 0;
        //gets(commandOG);

        //Used to look for spaces
        int readIndex = 0;
        //Used to write the final command one down
        int writeIndex;

        //This ensures that there are no spaces at the front.
        while (commandOG[readIndex] == ' ') {
            readIndex++;
        }
    
        //This ensures all the tabs and >1 spaces are reduced to one difference.
        for (writeIndex = 0; commandOG[readIndex] != '\0'; readIndex++) {
            if ((commandOG[readIndex] == ' ' && commandOG[readIndex - 1] == ' ') || (commandOG[readIndex] == ' ' && commandOG[readIndex - 1] == ';') || (commandOG[readIndex] == ' ' && commandOG[readIndex - 1] == '|')) {
                continue;
            }
            commandF1[writeIndex] = commandOG[readIndex];
            writeIndex++;
        }

        commandF1[writeIndex] = '\0';
        // printf("%s\n", commandF1);

        //Tokenizing the command in terms of the colon ie. ';' separates different commands
        char* tokenC;
        //Final command used to account for space
        char* commandF2 = commandF1;
        //To store the location after CD is used.
        char storeCWD[512];

        while (tokenC = strtok_r(commandF2, ";", &commandF2)) {

            if (pipeCount(tokenC) == 0) {

                //tokenC to be purely used for tokenizing, hence, this.
                char tokenX[512];
                strcpy(tokenX, tokenC);

                char* tokenS = strtok(tokenX, " ");

                if (strcmp(tokenS, "cd") == 0) {
                    cd_command(tokenS, storeCWD, homeDirectory);
                } else if ((strcmp(tokenS, "pwd") == 0)) {
                    pwd_command();
                } else if ((strcmp(tokenS, "echo") == 0)) {
                    echo_command(tokenS, 1, checkSign(tokenC));
                } else if (strcmp(tokenS, "ls") == 0) {
                    ls_command(tokenS, homeDirectory);
                } else if ((strcmp(tokenS, "repeat") == 0)) {
                    repeat_command(tokenS,  checkSign(tokenC));
                } else if ((strcmp(tokenS, "pinfo") == 0)) {
                    pinfo_command(tokenS);
                } else if ((strcmp(tokenS, "quit") == 0)) {
                    exit(0);
                } else if ((strcmp(tokenS, "cat") == 0)) {
                    cat_command(tokenS, 1, checkSign(tokenC));
                } else if ((strcmp(tokenS, "sort") == 0)) {
                    sort_command(tokenS, 1, checkSign(tokenC));
                } else if ((strcmp(tokenS, "jobs") == 0)) {
                    jobs_command(jobArray, bgCommand);
                } else if ((strcmp(tokenS, "fg") == 0)) {
                    int pid = fg_command(tokenS, jobArray);
                    if (pid < 0) {
                        pid *= -1;
                    };
                    removeBg(pid);
                    if (pid <= 0) {
                        error = 1;
                    }
                } else if ((strcmp(tokenS, "bg") == 0)) {
                    bg_command(tokenS, jobArray);
                } else if ((strcmp(tokenS, "sig") == 0)) {
                    sig_command(tokenS, jobArray);
                } else {
                    int pid = processes_command(tokenC);
                    if (pid < 0) {
                        error = 1;
                    } else if (pid > 0) {
                        addBg(pid, tokenX);
                    }
                }
            } else {

                char tokenY[512];
                strcpy(tokenY, tokenC);

                piping_command(tokenY, pipeCount(tokenY));

            }
        }
    }
    return 0;
}
