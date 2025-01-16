#include "s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  int i = 0, j;
  void *result = S21_NULL;
  while (str1[i] != '\0' && result == S21_NULL) {
    j = 0;
    while (str2[j] != '\0' && result == S21_NULL) {
      if (str1[i] == str2[j]) {
        result = (char *)&str1[i];
      }
      ++j;
    }
    ++i;
  }
  return result;
}
