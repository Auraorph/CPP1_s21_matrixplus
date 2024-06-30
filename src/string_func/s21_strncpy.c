#include "../s21_string.h"

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *ret = dest;
  for (; n > 0 && *src != '\0'; n--, dest++, src++) *dest = *src;
  if (n > 0 && *src == '\0') *dest = *src;
  return ret;
}