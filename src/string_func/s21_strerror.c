#include "s21_strerror.h"

#include "../s21_string.h"

char *s21_strerror(int errnum) {
  static char *strer = s21_NULL;
  char tmp[20] = {0};
  static char arr[50];
  char *newline = arr;
  s21_memset(newline, '\0', 50);
#if defined(__APPLE__)
  s21_memcpy(newline, "Unknown error: ", 16);
#elif defined(__linux__)
  s21_memcpy(newline, "Unknown error ", 16);
#endif
  int err = sizeof(strerrors) / sizeof(strerrors[0]);
  if (errnum < 0 || errnum >= err) {
    intToString(errnum, tmp);
    s21_strncat(newline, tmp, 20);
    strer = newline;
  } else
    strer = (char *)strerrors[errnum];
  return strer;
}