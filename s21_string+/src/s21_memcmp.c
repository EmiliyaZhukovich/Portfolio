#include "s21_string.h"

// 2. Compares the first n bytes of str1 and str2
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int compare = 0;
  // Посимвольное сравнение с досрочным выходом, если есть отличие
  for (s21_size_t i = 0; i < n && compare == 0; i++) {
    compare = *((char *)str1 + i) - *((char *)str2 + i);
  }
  return compare;
}
