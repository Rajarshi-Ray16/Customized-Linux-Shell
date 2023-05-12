#include "sign.h"

int checkSign(char* str) {
    
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        if (str[i] == '<') {
            for (int j = i; j < len; j++) {
                if (str[j] == '>') {
                    if (str[j + 1] == '>') {
                        return 5;
                    }
                    return 3;
                }
            }
            return 1;
        }
        if (str[i] == '>') {
            if (str[i + 1] == '>') {
                return 4;
            }
            return 2;
        }
        if (str[i] == '&') {
            return 6;
        }
    }

    return 0;

}

int pipeCount(char* command) {

    int pipeCount = 0;
    int len = strlen(command);

    for (int i = 0; i < len; i++) {
        if (command[i] == '|') {
            pipeCount++;
        }
    }

    return pipeCount;

}