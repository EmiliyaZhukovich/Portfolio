#include "s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int return_value;
  while (*str1 && n && *str1 == *str2) {
    str1++;
    str2++;
    --n;
  }
  if (n == 0) {
    return_value = 0;
  } else {
    return_value = *str1 - *str2;
  }
  return return_value;
}
