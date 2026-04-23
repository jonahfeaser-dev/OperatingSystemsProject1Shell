#include "commands.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

char *paths[500];
int pathCount = 0;

void initPaths(void) {
  paths[0] = malloc(strlen("/bin") + 1);
  strcpy(paths[0], "/bin");
  pathCount = 1;
}

void handleExit(int arguments, char *input[]) {
  
  if(arguments != 1) {
  
    fprintf(stderr, "An error has occurred\n");

  } else {
  
  exit(0);

  }

  }


int handleCD(int arguments, char *input[]) {
  
  if(arguments != 2) {
    fprintf(stderr, "An error has occurred\n");
  } else {
    chdir(input[1]);
  }
  
  return 0;
  
  }

void handlePath(int arguments, char *input[]) {
  for (int i = 0; i < pathCount; i++) {
    free(paths[i]);
    paths[i] = NULL;
  }

  pathCount = 0;
  
  if(arguments == 1) {
    return;
  } else {
    for(int i = 0; i < arguments - 1; i++) {
      paths[i] = strdup(input[i + 1]);
      pathCount++;
    }
  }
}

char searchPath[500];

int handleSearch(int arguments, char *input[]) {
  
  if(pathCount <= 0) {
    fprintf(stderr, "An error has occurred\n");
    return 1;
  }
  int commandFound = 0;
  for(int i = 0; i < pathCount; i++) {
    sprintf(searchPath, "%s/%s", paths[i], input[0]);
  
    if(access(searchPath, X_OK) == 0) {
      commandFound = 1;
      break;
    }
  }
  if(commandFound != 1) {
    fprintf(stderr, "An error has occurred\n");
    return 1;
  }
  return 0;
}

int executeCommand(char *input[]) {
  int pc = fork();

  if(pc < 0) {
    printf("Fork failed to occur\n");
    exit(1);
    } else if(pc == 0) {
    execv(searchPath, input);
    fprintf(stderr, "An error has occurred\n");
    exit(1);
    } else {
      wait(NULL);
      return pc;
    }
  return 0;
}


