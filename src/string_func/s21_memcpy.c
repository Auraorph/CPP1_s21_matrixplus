#include "../s21_string.h"

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *ret = dest;
  for (; n > 0; n--, ret++, src++) *ret = *(unsigned char *)src;
  return dest;
}