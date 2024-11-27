#ifndef S21_CAT_H
#define S21_CAT_H

#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct args {
  int b, n, s, E, T, v;
} args;

args argument_parser(int argc, char** argv);
int is_empty_line(const char* line, int len);
char v_output(unsigned char ch);
void outline(args* arg, char* line, int n);
void output(args* arg, const char* filename, int* line_count);

#endif
