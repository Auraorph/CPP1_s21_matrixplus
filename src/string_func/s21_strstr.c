#include "../s21_string.h"

char *s21_strstr(const char *haystack, const char *needle) {
  char *ret = s21_NULL;
  if (*needle == '\0')
    ret = (char *)haystack;
  else {
    int flag = 0;
    for (; *haystack != '\0' && flag == 0; haystack++)
      if (*haystack == *needle) flag = checkSubString(haystack, needle);
    if (flag == 1) ret = (char *)--haystack;
  }
  return ret;
}