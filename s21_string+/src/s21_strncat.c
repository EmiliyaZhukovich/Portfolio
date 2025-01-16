#include "s21_string.h"

// 7. Appends the string pointed to, by src to the end of the string pointed to,
// by dest up to n characters long.
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *out = dest;
  // Перестановка указателя в конец строки dest
  dest = dest + s21_strlen(dest);
  // Доп. условие выхода при досрочном окончании строки src
  while (n > 0 && *src != 0) {
    *dest = *src;
    dest++;
    src++;
    n--;
  }
  // Завершение строки спец символом
  *dest = '\0';
  return out;
}
