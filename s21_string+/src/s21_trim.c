#include <stdlib.h>

#include "s21_string.h"
void *s21_trim(const char *src, const char *trim_chars) {
  char *space = " ";
  const char *chars = space;
  if (trim_chars) {
    if (*trim_chars) {
      chars = trim_chars;
    }
  }
  s21_size_t length_src = 0;
  if (src) length_src = s21_strlen(src);
  char *reverse = (char *)malloc(sizeof(char) * (length_src + 1));
  // Переворот строки
  for (s21_size_t i = 0; i < length_src; i++) {
    reverse[i] = src[length_src - 1 - i];
  }
  reverse[length_src] = '\0';
  s21_size_t begin_segment = 0;
  s21_size_t end_segment = 0;
  if (src) {
    // Длина начального сегмента, состоящего из заданных символов
    begin_segment = s21_strspn(src, chars);
    // Длина конечного сегмента, состоящего из заданных символов
    end_segment = s21_strspn(reverse, chars);
  }
  s21_size_t length_out = 1;
  if (begin_segment != length_src) {
    length_out = length_src + 1 - begin_segment - end_segment;
  }
  // Итоговая строка
  char *out = (char *)malloc(length_out);
  if (out != S21_NULL) {
    for (s21_size_t i = 0; i < (length_out); i++) {
      out[i] = src[begin_segment + i];
    }
    out[length_out - 1] = '\0';
  }
  free(reverse);
  return out;
}
