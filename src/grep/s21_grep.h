#ifndef S21_GREP_H
#define S21_GREP_H

#define _POSIX_C_SOURCE 200809L
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct args {
  int e, i, v, c, l, n, h, s, f, o;
  char *pattern;

  int len_pattern;

} args;

void pattern_add(args *arg, char *pattern);
void add_reg_from_file(args *arg, const char *path);
args argument_parser(int argc, char **argv);
void output_line(char *line, int n);
void print_match(regex_t *re, char *line);
void processFile(args arg, const char *path, regex_t *reg);
void output(args arg, int argc, char **argv);

#endif