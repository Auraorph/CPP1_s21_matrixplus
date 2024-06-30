#include "../s21_string.h"

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *ret = (unsigned char *)str;
  for (; n > 0; n--, ret++) *ret = (unsigned char)c;
  return str;
}