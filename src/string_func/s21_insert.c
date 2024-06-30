#include "../s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  if (src == s21_NULL)
    return s21_NULL;
  else if (str == s21_NULL)
    return s21_NULL;

  int len = s21_strlen(str) + s21_strlen(src);
  char *ret = malloc(len + 1);
  if (ret == s21_NULL) return s21_NULL;
  s21_memset(ret, '0', len);
  ret[len] = '\0';

  char *srcRet = ret;
  int flagErr = 0;
  s21_size_t i = 0;

  for (; i < start_index && *src != '\0'; i++, ret++, src++) *ret = *src;

  if (i != start_index) {
    flagErr = 1;
    *ret = '\0';
  }

  for (; *str != '\0' && *ret != '\0'; ret++, str++) *ret = *str;

  for (; *src != '\0' && *ret != '\0'; ret++, src++) *ret = *src;

  if (*ret != '\0' || *src != '\0' || *str != '\0') flagErr = 1;

  if (flagErr == 1) {
    free(srcRet);
    srcRet = s21_NULL;
  }

  return srcRet;
}