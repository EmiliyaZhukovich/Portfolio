#include "s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t haystack_lenght = s21_strlen(haystack);
  s21_size_t needle_lenght = s21_strlen(needle);
  const char *result = S21_NULL;

  if (haystack_lenght < needle_lenght) {
    result = S21_NULL;
  } else if (haystack_lenght == needle_lenght &&
             !s21_strcmp(haystack, needle)) {
    result = haystack;
  } else if (needle_lenght == 0) {
    result = haystack;
  } else {
    for (s21_size_t i = 0; i <= haystack_lenght - needle_lenght; ++i) {
      for (s21_size_t j = 0; j <= needle_lenght && !result; ++j) {
        if (haystack[i + j] != needle[j]) {
          result = S21_NULL;
          break;
        } else if (j == needle_lenght - 1) {
          result = haystack + i;
        }
      }
    }
  }
  return (char *)result;
}
