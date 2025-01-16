#include "s21_string.h"

// 17. Searches for the last occurrence of the character c (an unsigned char) in
// the string pointed to by the argument str.
char *s21_strrchr(const char *str, int c) {
  const char *out = S21_NULL;
  do {
    if (*str == c) {
      out = str;
    }
  } while (*str++);
  return (char *)out;
}
