#ifndef COMMANDS_H
#define COMMANDS_H

extern char searchPath[500];

void initPaths(void);

void handleExit(int arguments, char *input[]);

int handleCD(int arguments, char *input[]);

void handlePath(int arguments, char *input[]);

int handleSearch(int arguments, char *input[]);

int executeCommand(char *input[]);
#endif
