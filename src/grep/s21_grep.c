#include "s21_grep.h"

void pattern_add(args *arg, char *pattern) {
  if (arg->len_pattern != 0) {
    strcat(arg->pattern + arg->len_pattern, "|");
    arg->len_pattern++;
  }
  arg->len_pattern += sprintf(arg->pattern + arg->len_pattern, "(%s)", pattern);
}

void add_reg_from_file(args *arg, const char *path) {
  FILE *f = fopen(path, "r");
  if (!f) {
    if (!arg->s) {
      perror(path);
    }
    return;
  }

  char *line = NULL;
  size_t memline = 0;
  ssize_t read = 0;

  while ((read = getline(&line, &memline, f)) != -1) {
    if (line[read - 1] == '\n') {
      line[read - 1] = '\0';
    }
    pattern_add(arg, line);
  }

  free(line);
  fclose(f);
}

void cleanup(args *arg) {
  if (arg->pattern) {
    free(arg->pattern);
  }
}

args argument_parser(int argc, char **argv) {
  args arg = {0};
  arg.pattern = malloc(1024);
  if (arg.pattern == NULL) {
    perror("Failed to allocate memory for pattern");
    exit(1);
  }
  arg.pattern[0] = '\0';

  int opt;
  while ((opt = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    switch (opt) {
      case 'e':
        arg.e = 1;
        pattern_add(&arg, optarg);
        break;
      case 'i':
        arg.i = REG_ICASE;
        break;
      case 'v':
        arg.v = 1;
        break;
      case 'c':
        arg.c = 1;
        break;
      case 'l':
        arg.l = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 'h':
        arg.h = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'f':
        arg.f = 1;
        add_reg_from_file(&arg, optarg);
        break;
      case 'o':
        arg.o = 1;
        break;
      case '?':
        fprintf(stderr, "Unknown option: %c\n", optopt);
        cleanup(&arg);
        exit(1);
      default:
        break;
    }
  }

  if (arg.len_pattern == 0 && optind < argc) {
    pattern_add(&arg, argv[optind]);
    optind++;
  }
  if (argc - optind == 1) {
    arg.h = 1;
  }
  return arg;
}

void output_line(char *line, int n) {
  for (int i = 0; i < n; i++) {
    putchar(line[i]);
  }
  if (line[n - 1] != '\n') {
    putchar('\n');
  }
}

void print_match(regex_t *re, char *line) {
  regmatch_t match;
  int offset = 0;

  while (1) {
    int result = regexec(re, line + offset, 1, &match, 0);
    if (result != 0) {
      break;
    }
    for (int i = match.rm_so; i < match.rm_eo; i++) {
      putchar(line[offset + i]);
    }
    putchar('\n');
    offset += match.rm_eo;
  }
}

void processFile(args arg, const char *path, regex_t *reg) {
  FILE *f = fopen(path, "r");
  if (!f) {
    if (!arg.s) {
      perror(path);
    }
    return;
  }

  char *line = NULL;
  size_t memline = 0;
  ssize_t read = 0;
  int c = 0;
  int line_count = 1;

  while ((read = getline(&line, &memline, f)) != -1) {
    int result = regexec(reg, line, 0, NULL, 0);
    if ((result == 0 && !arg.v) || (arg.v && result != 0)) {
      if (!arg.c && !arg.l) {
        if (!arg.h) printf("%s:", path);
        if (arg.n) printf("%d:", line_count);
        if (arg.o) {
          print_match(reg, line);
        } else {
          output_line(line, read);
        }
      }
      c++;
    }
    line_count++;
  }

  free(line);
  if (arg.c && !arg.l) {
    if (!arg.h) printf("%s:", path);
    printf("%d\n", c);
  }
  if (arg.l && c > 0) {
    printf("%s\n", path);
  }
  fclose(f);
}

void output(args arg, int argc, char **argv) {
  regex_t re;
  int error = regcomp(&re, arg.pattern, REG_EXTENDED | arg.i);
  if (error) {
    perror("ERROR");
    cleanup(&arg);
    exit(1);
  }

  for (int i = optind; i < argc; i++) {
    processFile(arg, argv[i], &re);
  }
  regfree(&re);
}

int main(int argc, char *argv[]) {
  args arg = argument_parser(argc, argv);
  output(arg, argc, argv);
  cleanup(&arg);
  return 0;
}
