#include "sleep.h"

void sleep_command(char* tokenS) {
    tokenS = strtok(NULL, " ");
    sleep(atoi(tokenS));
}