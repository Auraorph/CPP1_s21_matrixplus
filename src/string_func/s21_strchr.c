#include "../s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *ret = s21_NULL;
  for (; *str != '\0' && ret == s21_NULL; str++)
    if (*str == c) ret = (char *)str;
  if ((*str == '\0' && c == '\0') || c == '\0') ret = (char *)str;
  return ret;
}