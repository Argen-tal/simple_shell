#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stddef.h>

#define _NULL ((void *)0)
#define X_OK 1

int main(int argc, char **argv, char **env);
int execute(char **args, char **env);
void sigint_handler(int signum);
char *find_path(char *cmd, char **env);
char *_getenv(const char *name, char **env);
size_t _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest const char *sec);
int _strcmp(const char *s1, const char *s2);
void print_env(char **env);

#endif
