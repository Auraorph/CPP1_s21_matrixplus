#include "../s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *ret = NULL;
  for (; n > 0 && ret == NULL; n--, str++)
    if (*(unsigned char *)str == (unsigned char)c) ret = (unsigned char *)str;
  return ret;
}