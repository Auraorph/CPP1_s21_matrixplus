#include "../s21_string.h"

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t ret = 0;
  int flag = 0;
  for (; *str1 != '\0' && flag == 0; str1++)
    if (!checkSubChar(str1, str2))
      ret++;
    else
      flag = 1;
  return ret;
}