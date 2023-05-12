#include "repeat.h"

void repeat_command(char* tokenS, int flag) {

    tokenS = strtok(NULL, " ");
    int t = atoi(tokenS);
    tokenS = strtok(NULL, " ");
                
    if ((strcmp(tokenS, "echo") == 0)) {
        echo_command(tokenS, t, flag);
    } else if ((strcmp(tokenS, "cat") == 0)) {
        cat_command(tokenS, t, flag);
    } else if ((strcmp(tokenS, "sleep") == 0)) {
        tokenS = strtok(NULL, " ");
        sleep(atoi(tokenS) * t);
    }

}