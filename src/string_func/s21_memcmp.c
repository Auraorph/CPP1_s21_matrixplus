#include "../s21_string.h"

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int flag = 0;
  for (; n > 0 && flag == 0; n--, str1++, str2++)
    flag = *(unsigned char *)str1 - *(unsigned char *)str2;
  return flag == 0 ? flag : flag < 0 ? -1 : 1;
}