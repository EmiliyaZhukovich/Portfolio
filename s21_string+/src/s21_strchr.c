#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  const char *result = S21_NULL;
  for (s21_size_t length = 0; length < s21_strlen(str) + 1; length++) {
    if (str[length] == c) {
      result = &str[length];
      break;
    }
  }
  return (char *)result;
}
