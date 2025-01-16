#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t length = 0;
  while (*str1) {
    //  проверяем, входит ли символ str1 в перечень символов str2
    if (!s21_strchr(str2, *str1)) {
      break;
    } else {
      str1++;
      length++;
    }
  }
  return length;
}
