#include <stdlib.h>

#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *out = S21_NULL;
  s21_size_t length_str = (str) ? s21_strlen(str) : 0;
  s21_size_t length = 0;
  if (src && (start_index <= s21_strlen(src))) {
    length = length_str + s21_strlen(src);
    out = (char *)malloc(length + 1);
  }
  if (out != S21_NULL) {
    for (s21_size_t i = 0; i < length; i++) {
      // Вставка строки str
      if (i >= start_index && *str) {
        out[i] = *str;
        str++;
        // Вставка основной строки src
      } else {
        out[i] = *src;
        src++;
      }
    }
    out[length] = '\0';
  }
  return out;
}
