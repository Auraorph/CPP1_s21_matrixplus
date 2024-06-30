#include "../s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == s21_NULL) return s21_NULL;

  int len = s21_strlen(str);
  char *ret = malloc(len + 1);
  if (ret == s21_NULL) return s21_NULL;
  s21_memcpy(ret, str, len);
  ret[len] = '\0';
  char *srcRet = ret;

  for (; *ret != '\0'; ret++)
    if (*ret >= 'a' && *ret <= 'z') *ret -= 32;

  return srcRet;
}