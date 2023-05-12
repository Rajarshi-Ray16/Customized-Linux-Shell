#ifndef __SIG__
#define __SIG__

#include "headings.h"

extern int errno;

int sig_command(char* tokenS, int* jobArray);

#endif