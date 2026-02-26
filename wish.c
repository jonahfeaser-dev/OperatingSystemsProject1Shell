#include "wish.h"
#include "commands.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int run_wish(int argc, char *argv[]) {
  initPaths();
  if (argc > 1) {
    FILE *fptr = fopen(argv[1], "r");

    if (fptr == NULL) {
      printf("Error: Could not open the file.\n");
      return 1;
    }

    char *line = NULL;
    size_t length = 0; 
    ssize_t nread;
    char *arguments[100];
    char *found;

    while ((nread = getline(&line, &length, fptr)) != -1) {

      int i = 0;
      char *copy = line;
      while( (found = strsep(&copy, " \t\n")) != NULL) {
        
        if(found[0] != '\0') {
        arguments[i] = found;
        i++;
        }
     }
      arguments[i] = NULL;

      if(strcmp(arguments[0], "exit") == 0) {

        handleExit(i, arguments);
      } else if(strcmp(arguments[0], "cd") == 0) {
        
        handleCD(i, arguments);

      } else if(strcmp(arguments[0], "path") == 0) {

        handlePath(i, arguments);

      } else {

        handleSearch(i, arguments);
  }
}

    free(line);
    fclose(fptr);

  } else {
    char *line = NULL;
    size_t length = 0;
    int lineNum = 1;
    ssize_t nread;

    while (1) {
      printf("wish> ");
      nread = getline(&line, &length, stdin);

      if (nread == -1) {
        break;
      }

      if (strcmp(line, "exit\n") == 0) {
        break;
      }

      printf("line%d: %s", lineNum, line);
      lineNum++;
    }

    free(line);
  }

  return 0;
}

