#include "../s21_string.h"

void* s21_trim(const char* src, const char* trim_chars) {
  if (src == s21_NULL)
    return s21_NULL;
  else if (trim_chars == s21_NULL) {
    int len = s21_strlen(src);
    char* ret = malloc(len + 1);
    s21_memcpy(ret, src, len);
    ret[len] = '\0';
    return ret;
  }
  int flag = 1;
  for (; *src != '\0' && flag == 1; src++) {
    if (src != s21_strpbrk(src, trim_chars)) {
      src--;
      flag = 0;
    }
  }

  int len = s21_strlen(src);
  char* ret = malloc(len + 1);
  char* srcRet = ret;
  if (ret != s21_NULL) {
    s21_memcpy(ret, src, len);
    ret[len] = '\0';

    ret += len > 0 ? len - 1 : 0;
    for (; ret == s21_strpbrk(ret, trim_chars); ret--) {
      *ret = '\0';
    }
  }
  return srcRet;
}