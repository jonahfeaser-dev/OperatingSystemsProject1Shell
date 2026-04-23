#include "wish.h"
#include "redirect.h"
#include "commands.h"
#include "parallel.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int run_wish(int argc, char *argv[]) {
  initPaths();
  if (argc == 2) {
    FILE *fptr = fopen(argv[1], "r");

    if (fptr == NULL) {
      fprintf(stderr, "An error has occurred\n");
      return 1;
    }

   char *line = NULL;
    size_t length = 0;
    ssize_t nread;
    char *arguments[100];
    char *found;
    int redirect = 0;
    int parallel = 0;

    while ((nread = getline(&line, &length, fptr)) != -1) {

      int i = 0;
      redirect = 0;
      parallel = 0;
      char *copy = line;

      while ((found = strsep(&copy, " \t\n")) != NULL) {

        while (found[0] != '\0') {
          int split = 0;

          for (int j = 0; found[j] != '\0'; j++) {
            if (found[j] == '>' || found[j] == '&') {
              char symbol = found[j];
              found[j] = '\0';

              if (found[0] != '\0') {
                arguments[i] = found;
                i++;
              }

              if (symbol == '>') {
                arguments[i] = ">";
                redirect = 1;
              } else {
                arguments[i] = "&";
                parallel = 1;
              }
              i++;

              found = &found[j + 1];
              split = 1;
              break;
            }
          }

          if (!split) {
            arguments[i] = found;
            i++;
            break;
          }
        }
        }    
      arguments[i] = NULL;
      if (i == 0) {
        continue;
      }
      if(strcmp(arguments[0], "exit") == 0) {

        handleExit(i, arguments);
      } else if(strcmp(arguments[0], "cd") == 0) {
        
        handleCD(i, arguments);

      } else if(strcmp(arguments[0], "path") == 0) {

        handlePath(i, arguments);

      } else if(parallel == 1) {

        handleParallel(i, arguments);
        
      } else if(redirect == 1) {

        handleRedirect(i, arguments);

      } else {
        
        if(handleSearch(i, arguments) == 0) {

          executeCommand(arguments);
        }
      }
    }

    free(line);
    fclose(fptr);

  } else if(argc == 1) {
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
  } else {
    fprintf(stderr, "An error has occurred\n");
    return 1;
  }

  return 0;
}
