#include "redirect.h"
#include "commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>


void handleRedirect(int arguments, char *input[]) {

  int redirectIndex = 0;

  for(int i = 0; i < arguments; i++) {
    if(strcmp(input[i], ">") == 0) {
      redirectIndex = i;
      break;
    }
  }

  if(redirectIndex == 0 ||  (arguments - 2) != redirectIndex) {
    fprintf(stderr, "An error has occurred\n");
  } else {


  char *preRedirectInput[100];

  for(int i = 0; i < redirectIndex; i++) {
    preRedirectInput[i] = input[i];
  }

  preRedirectInput[redirectIndex] = NULL;

  if(handleSearch(redirectIndex, preRedirectInput) != 0) {
    return; 
  }

  FILE *fptr;

  fptr = fopen(input[redirectIndex + 1], "w");
  
  if(fptr == NULL) {
    fprintf(stderr, "An error has occurred\n");
    return;
  }
  executeRedirectCommand(fptr, preRedirectInput);

  fclose(fptr);
  } 
}

int executeRedirectCommand(FILE *fptr, char *input[]) {

  int pc = fork();

  if(pc < 0) {
    printf("Fork failed to occur\n");
    exit(1);
  } else if(pc == 0) {
    int fd = fileno(fptr);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    execv(searchPath, input);
    fprintf(stderr, "An error has occurred\n");
    exit(1);
  } else {
    wait(NULL);
    return pc;
  }
  return 0;
}
