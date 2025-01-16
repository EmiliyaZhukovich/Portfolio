#include "s21_string.h"

int is_delim(char c, const char *delim) {
  int flag = 0;
  while (*delim != '\0') {
    if (c == *delim) {
      flag = 1;
    }
    delim++;
  }
  return flag;
}

char *s21_strtok(char *str, const char *delim) {
  static char *start_point;  // start of the next search
  char *result = S21_NULL;
  if (!str) {
    str = start_point;
  }
  if (str) {  // clearing the beginning of a string
    int all_deligms = 0;
    int regular = 0;
    while (regular == 0) {
      if (is_delim(*str, delim)) {
        str++;
      } else if (*str == '\0') {
        all_deligms = 1;
        regular = 1;
        // we've reached the end of the string
        // and no regular character was there
      } else {
        regular = 1;  // we've found a regular character
      }
    }
    if (!all_deligms) {  // if the string still contains smth
      result = str;
      int flag = 1;
      while (flag == 1) {
        if (*str == '\0') {
          start_point = str;
          flag = 0;  // next execution will return NULL
        }
        if (is_delim(*str, delim)) {
          *str = '\0';
          start_point = str + 1;
          flag = 0;
        }
        str++;
      }
    }
  }
  return result;
}
