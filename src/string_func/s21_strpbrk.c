#include "../s21_string.h"

char *s21_strpbrk(const char *str1, const char *str2) {
  char *ret = s21_NULL;
  for (; *str1 != '\0' && ret == s21_NULL; str1++)
    if (checkSubChar(str1, str2)) ret = (char *)str1;
  return ret;
}