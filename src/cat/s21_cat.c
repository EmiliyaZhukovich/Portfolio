#include "s21_cat.h"

args argument_parser(int argc, char **argv) {
  args arg = {0};
  struct option long_options[] = {{"number", no_argument, NULL, 'n'},
                                  {"number-nonblank", no_argument, NULL, 'b'},
                                  {"squeeze-blank", no_argument, NULL, 's'},
                                  {0, 0, 0, 0}};
  int opt;
  while ((opt = getopt_long(argc, argv, "bnsEeTtv", long_options, 0)) != -1) {
    switch (opt) {
      case 'b':
        arg.b = 1;
        break;
      case 'n':
        arg.n = 1;
        break;
      case 's':
        arg.s = 1;
        break;
      case 'e':
        arg.E = 1;
        arg.v = 1;
        break;
      case 'E':
        arg.E = 1;
        break;
      case 'T':
        arg.T = 1;
        break;
      case 't':
        arg.T = 1;
        arg.v = 1;
        break;
      case '?':
        fprintf(stderr, "Unknown option: %c\n", opt);
        exit(1);
      default:
        break;
    }
  }
  return arg;
}

char v_output(unsigned char ch) {
  if (ch == '\n' || ch == '\t') return ch;

  if (ch <= 31) {
    putchar('^');
    return ch + 64;
  } else if (ch == 127) {
    putchar('^');
    return '?';
  } else if (ch > 127) {
    printf("M-%c", ch - 128);
    return ch;
  }
  return ch;
}

void outline(args *arg, char *line, int n) {
  for (int i = 0; i < n; i++) {
    if (arg->T && line[i] == '\t') {
      printf("^I");
      continue;
    }
    if (arg->E && line[i] == '\n') {
      putchar('$');
    }
    if (arg->v) {
      putchar(v_output(line[i]));
    } else {
      putchar(line[i]);
    }
  }
}

int is_empty_line(const char *line, int len) {
  for (int i = 0; i < len; i++) {
    if (line[i] != ' ' && line[i] != '\n') {
      return 0;
    }
  }
  return 1;
}

void output(args *arg, const char *filename, int *line_count) {
  FILE *f = fopen(filename, "r");
  if (!f) {
    fprintf(stderr, "Cannot open file %s: ", filename);
    perror("");
    return;
  }

  char *line = NULL;
  size_t memline = 0;
  int read = 0;
  int last_line_was_empty = 0;

  while ((read = getline(&line, &memline, f)) != -1) {
    int is_empty = is_empty_line(line, read);

    if (arg->s && is_empty) {
      if (last_line_was_empty) {
        continue;
      }
      last_line_was_empty = 1;
    } else {
      last_line_was_empty = 0;
    }

    if (arg->b) {
      if (!is_empty) {
        printf("%6d\t", (*line_count)++);
      }
    } else if (arg->n) {
      printf("%6d\t", (*line_count)++);
    }

    outline(arg, line, read);
  }

  free(line);
  fclose(f);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "Usage: %s [options] file...\n", argv[0]);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  -b, --number-nonblank    Number non-blank lines\n");
    fprintf(stderr, "  -n, --number             Number all lines\n");
    fprintf(stderr,
            "  -s, --squeeze-blank      Suppress repeated empty lines\n");
    fprintf(stderr,
            "  -e                       Same as -E, but also show "
            "non-printable characters\n");
    fprintf(stderr,
            "  -E                       Display $ at end of each line\n");
    fprintf(stderr,
            "  -T                       Display TAB characters as ^I\n");
    fprintf(stderr,
            "  -t                       Same as -T, but also show "
            "non-printable characters\n");

    return 1;
  }

  args arg = argument_parser(argc, argv);
  int line_count = 1;

  for (int i = optind; i < argc; i++) {
    output(&arg, argv[i], &line_count);
  }

  return 0;
}
