#include "s21_string.h"

char *s21_strcpy(char *dest, const char *src) {
  char *result = dest;
  for (; (*dest = *src) != '\0'; dest++, src++) {
  }
  return result;
}
