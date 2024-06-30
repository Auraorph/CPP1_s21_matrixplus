#include "../s21_string.h"

int checkSubChar(const char *str1, const char *str2) {
  int ret = 0;
  for (; ret == 0 && *str2 != '\0'; str2++)
    if (*str1 == *str2) ret = 1;
  return ret;
}

int checkSubString(const char *str1, const char *str2) {
  int flag = 0;
  for (; *str1 == *str2 && *str1 != '\0'; str1++, str2++)
    ;
  if (*str2 == '\0') flag = 1;
  return flag;
}

char *intToString(int digit, char *ret) {
  int flag = 0;
  int minusflag = 0;
  if (digit < 0) minusflag = 1;
  for (int i = 0; i < 40 && flag == 0; i++) {
    if (digit == 0)
      flag = 1;
    else {
      ret[i] = minusflag == 0 ? '0' + (digit % 10) : '0' - (digit % 10);
      digit /= 10;
    }
  }
  char tempCh;
  int len = s21_strlen(ret);
  if (minusflag == 1) ret[len++] = '-';
  for (int i = 0; i < len / 2; i++) {
    tempCh = ret[i];
    ret[i] = ret[len - 1 - i];
    ret[len - 1 - i] = tempCh;
  }
  return ret;
}

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t ret = 0;
  int flag = 0;
  for (; *str1 != '\0' && flag == 0; str1++)
    if (checkSubChar(str1, str2))
      ret++;
    else
      flag = 1;
  return ret;
}