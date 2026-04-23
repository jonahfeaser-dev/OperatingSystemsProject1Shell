#ifndef REDIRECT_H
#define REDIRECT_H

#include <stdio.h>

void handleRedirect(int arguments, char *input[]);

int executeRedirectCommand(FILE *fptr, char *input[]);

#endif
