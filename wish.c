#include "wish.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

int run_wish(int argc, char *argv[]) {
  char batchMode[] = "batch.txt";

  if (argc > 1 && strcmp(argv[1], batchMode) == 0) {
    FILE *fptr = fopen("batch.txt", "r");

    if (fptr == NULL) {
      printf("Error: Could not open the file.\n");
      return 1;
    }

    char *line = NULL;
    size_t length = 0;
    int lineNum = 1;
    ssize_t nread;

    while ((nread = getline(&line, &length, fptr)) != -1) {
      printf("line%d: %s", lineNum, line);
      lineNum++;
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

