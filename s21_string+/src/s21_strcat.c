#include "s21_string.h"

char *s21_strcat(char *dest, const char *src) {
  int i = 0, j = 0;
  while (dest[i] != '\0') i++;
  while (src[j] != '\0') {
    dest[i] = src[j];
    i++;
    j++;
  }
  return (char *)dest;
}
