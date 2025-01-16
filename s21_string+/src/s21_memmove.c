#include "s21_string.h"

void *s21_memmove(void *dest, const void *src, s21_size_t len) {
  s21_size_t i;
  i = 0;
  if (len == 0 || src == dest) return (dest);
  if (dest > src && dest < src + len) {
    while (len--) ((unsigned char *)dest)[len] = ((unsigned char *)src)[len];
    return (dest);
  } else {
    while (i++ < len) {
      *((unsigned char *)dest) = *((unsigned char *)src);
      ++dest;
      ++src;
    }
  }
  return (dest - len);
}
