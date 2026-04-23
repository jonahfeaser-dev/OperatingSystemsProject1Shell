#include "parallel.h"
#include "commands.h"
#include "redirect.h"
#include "wish.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void handleLine(int arguments, char *input[]) {

int redirect = 0;

for(int i = 0; i < arguments; i++) {
  if(strcmp(input[i], ">") == 0) {
    redirect = 1;
    }
}

      if(strcmp(input[0], "exit") == 0) {

        handleExit(arguments, input);
      } else if(strcmp(input[0], "cd") == 0) {

        handleCD(arguments, input);

      } else if(strcmp(input[0], "path") == 0) {

        handlePath(arguments, input);

      } else if(redirect == 1) {

        handleRedirect(arguments, input);

      } else {

        if(handleSearch(arguments, input) == 0) {

          executeCommand(input);
        }
      }
    }

void handleParallel(int arguments, char *input[]) {
  
  int index = 0;
  while(index < arguments) {
  char *temp[50];
  int i = 0;
  while(index < arguments && strcmp(input[index], "&") != 0) {
  
    temp[i] = input[index];
    index++;
    i++;    
  }
  if(index < arguments && strcmp(input[index], "&") == 0) {
  index++;
  }
  temp[i] = NULL;  
      int rc = fork();
      if(rc < 0) {
        fprintf(stderr, "An error has occurred\n");
        exit(1);
      } else if(rc == 0) {
        handleLine(i, temp); 
        exit(0);
      } else {
      
      }
    }
  while(wait(NULL) > 0);
  }

