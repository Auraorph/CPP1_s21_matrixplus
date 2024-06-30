#include "../s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ret = dest;
  for (; *dest != '\0'; dest++)
    ;
  for (; n > 0 && *src != '\0'; n--, dest++, src++) *dest = *src;
  return ret;
}