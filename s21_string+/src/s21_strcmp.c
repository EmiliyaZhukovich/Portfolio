#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
  s21_size_t c1 = 0;
  s21_size_t c2 = 0;

  do {
    c1 = *str1++;
    c2 = *str2++;
  } while (c1 == c2 && c1 && c2);

  return c1 - c2;
}
