#ifndef COMMANDS_H
#define COMMANDS_H

void initPaths(void);

void handleExit(int arguments, char *input[]);

int handleCD(int arguments, char *input[]);

void handlePath(int arguments, char *input[]);

int handleSearch(int arguments, char *input[]);

#endif
