#include "../s21_string.h"

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int flag = 0;
  for (; n > 0 && flag == 0; n--, str1++, str2++) flag = *str1 - *str2;
  return flag;
}