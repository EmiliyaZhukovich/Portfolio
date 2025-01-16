#include "s21_string.h"

// 12. Copies up to n characters from the string pointed to, by src to dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *out = dest;
  int flag = 0;
  while (n > 0 && !flag) {
    flag = !src;
    *dest = *src;
    dest++;
    src++;
    n--;
  }
  return out;
}
