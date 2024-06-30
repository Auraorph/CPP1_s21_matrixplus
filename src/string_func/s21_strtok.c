#include "../s21_string.h"

char* s21_strtok(char* str, const char* delim) {
  static char* saveString = s21_NULL;
  int flag = 0;
  char* returnString = s21_NULL;
  //Если ввели NULL вместо строки, то тогда используется строка из токена
  if (str == s21_NULL) str = saveString;
  //Если указатель строки указывается на конец строки, это возврат NULL
  if (str == s21_NULL || *str == '\0') {
    saveString = str;
    flag = 1;
  }
  //Если указатель строки указывается на конец строки после разделительных
  //символов, это возврат NULL
  if (flag == 0 && *(str + s21_strspn(str, delim)) == '\0') {
    saveString = str + s21_strspn(str, delim);
    flag = 1;
  }
  if (flag == 0) {
    str += s21_strspn(str, delim);
    char* endString = str + s21_strcspn(str, delim);
    //Если это последний фрагмент строки, которую мы делим, то зануляем токен,
    //возращаем этот фрагмент
    if (*endString == '\0') saveString = endString;
    //Иначе отделяем строку
    else {
      *endString = '\0';
      saveString = endString + 1;
    }
    returnString = str;
  }
  return returnString;
}
