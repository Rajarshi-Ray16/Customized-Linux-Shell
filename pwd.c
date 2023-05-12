#include "pwd.h"

void pwd_command() {
  //Current Working Directory
  char cwd[512];
  getcwd(cwd, 512);
  printf("%s\n", cwd);
}