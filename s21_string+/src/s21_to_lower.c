#include <stdlib.h>

#include "s21_string.h"

// Returns a copy of string (str) converted to uppercase. In case of any error,
// return NULL
void *s21_to_lower(const char *str) {
  s21_size_t length = s21_strlen(str);
  char *out = (char *)malloc(length + 1);
  if (out != S21_NULL) {
    for (s21_size_t i = 0; i < (length + 1); i++) {
      if (*(str + i) >= 'A' && *(str + i) <= 'Z') {
        *(out + i) = *(str + i) + 32;
      } else {
        *(out + i) = *(str + i);
      }
    }
  }
  return out;
}
