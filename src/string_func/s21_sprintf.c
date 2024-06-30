#include "s21_sprintf.h"

int s21_sprintf(char* str, const char* format, ...) {
  va_list arg;
  va_start(arg, format);
  int flag = 0;
  char* srcStr = str;
  unsigned long j = 0;
  for (int i = 0; format[i] != '\0' && flag == 0; i++) {
    if (format[i] != '%') {
      *str = format[i];
      str++;
    } else {
      i++;
      if (s21_strpbrk((format + i), "cdieEfgGosuxXpn%") == s21_NULL)
        flag = 1;
      else {
        i = singleArgToStrint(str, srcStr, format, i, &arg, &j);
        str += j;
      }
    }
  }
  va_end(arg);
  *str = '\0';
  return str - srcStr;
}

int singleArgToStrint(char* str, char* srcStr, const char* format, int i,
                      va_list* arg, unsigned long* j) {
  flagsSprintf flags = {0};
  lengthSprintf length = {0};

  i += check1Flags((format + i), &flags);
  i += check2WidthOrAccuracy((format + i), &flags.width, arg);
  if (format[i] == '.') {
    flags.dot = 1;
    i++;
    i += check2WidthOrAccuracy((format + i), &flags.accuracy, arg);
  }
  i += check3Length((char*)(format + i), &length);
  *j = parserHub(str, srcStr, format[i], flags, length, arg);
  return i;
}

int check1Flags(const char* format, flagsSprintf* flags) {
  int plusI = 0;
  int flag = 0;
  while (flag == 0) {
    switch (*(format + plusI)) {
      case '-':
        flags->minus = 1;
        plusI++;
        break;
      case '+':
        flags->plus = 1;
        plusI++;
        break;
      case ' ':
        flags->space = 1;
        plusI++;
        break;
      case '#':
        flags->sharp = 1;
        plusI++;
        break;
      case '0':
        flags->zero = 1;
        plusI++;
        break;
      default:
        flag = 1;
        break;
    }
  }

  if (flags->plus == 1) flags->space = 0;
  if (flags->minus == 1) flags->zero = 0;

  return plusI;
}

int check2WidthOrAccuracy(const char* format, int* number, va_list* arg) {
  int plusI = 0;
  int flag = 0;
  while (flag == 0) {
    if (*(format + plusI) == '*') {
      *number = va_arg(*arg, int);
      plusI++;
    } else if (*(format + plusI) >= '0' && *(format + plusI) <= '9') {
      *number = stringToInt(format + plusI);
      for (int temp = *number; temp > 0; plusI++) temp /= 10;

      if (*number == 0) {
        plusI++;
        flag = 1;
      }
    } else
      flag = 1;
  }
  return plusI;
}

int stringToInt(const char* str) {
  int resoultInt = 0;
  int flagMinus = 0;
  if (*str == '-') {
    flagMinus = 1;
    str++;
  }
  for (size_t i = 0; i < DECIMAL100 && *str >= '0' && *str <= '9'; i++, str++)
    resoultInt = resoultInt * 10 + (*str - 48);
  if (flagMinus == 1) resoultInt *= (-1);
  return resoultInt;
}

int check3Length(char* str, lengthSprintf* length) {
  int plusI = 0;
  int flag = 0;
  while (flag == 0) {
    switch (*(str + plusI)) {
      case 'h':
        length->h = 1;
        plusI++;
        break;
      case 'l':
        length->l = 1;
        plusI++;
        break;
      case 'L':
        length->L = 1;
        plusI++;
        break;
      default:
        flag = 1;
        break;
    }
  }
  if (length->l == 1) length->h = 0;
  return plusI;
}

unsigned long parserHub(char* str, char* srcStr, char spec, flagsSprintf flags,
                        lengthSprintf length, va_list* arg) {
  unsigned long countElemInStr = 0;
  if (spec == 'c') {
    int ch = va_arg(*arg, int);
    countElemInStr = parserC(str, flags, (char)ch);
  } else if (spec == 'd' || spec == 'i') {
    countElemInStr = parserID(str, flags, length, arg);
  } else if (spec == 'e' || spec == 'E' || spec == 'g' || spec == 'G') {
    countElemInStr = parserEeGg(str, flags, length, arg, spec);
  } else if (spec == 'f') {
    countElemInStr = parserF(str, flags, length, arg);
  } else if (spec == 's') {
    countElemInStr = parserS(str, flags, arg);
  } else if (spec == 'o' || spec == 'u' || spec == 'x' || spec == 'X') {
    countElemInStr = parserOUxX(str, flags, length, arg, spec);
  } else if (spec == 'p') {
    flags.sharp = 1;
    countElemInStr = parserOUxX(str, flags, length, arg, spec);
  } else if (spec == 'n') {
    long* n = va_arg(*arg, long*);
    *n = (long)(str - srcStr);
  } else if (spec == '%') {
    countElemInStr = parserC(str, flags, '%');
  }
  return countElemInStr;
}

void reverseString(char* str) {
  int length = s21_strlen(str);
  int i, j;
  for (i = 0, j = length - 1; i < j; i++, j--) {
    char temp = str[i];
    str[i] = str[j];
    str[j] = temp;
  }
}

// for flags dieEfgGouxX
int ifAccuracyIntMoreLen(flagsSprintf flags, int len, char* intInString) {
  if (flags.accuracy > len) {
    int diff = flags.accuracy - len;
    char zeroString[diff + 1];  // diff + 1
    zeroString[diff] = '\0';
    myInsert2(intInString, s21_memset(zeroString, '0', diff), 0);
    len += diff;
  }
  return len;
}

char* widthMoreLen(flagsSprintf flags, int len, char* intInString, char* str,
                   int isFirstSign, char* firstSign) {
  if (flags.width > len) {
    int diff = flags.width - len;
    char zeroOrSpaceString[diff + 1];  // diff + 1
    zeroOrSpaceString[diff] = '\0';
    if (flags.zero == 1) {
      if (isFirstSign > 0) str = myInsert1(str, firstSign, 0);
      str = myInsert1(str, s21_memset(zeroOrSpaceString, '0', diff), 0);
      str = myInsert1(str, intInString, 0);
    } else {
      if (flags.minus == 0)
        str = myInsert1(str, s21_memset(zeroOrSpaceString, ' ', diff), 0);
      if (isFirstSign > 0) str = myInsert1(str, firstSign, 0);
      str = myInsert1(str, intInString, 0);
      if (flags.minus == 1)
        str = myInsert1(str, s21_memset(zeroOrSpaceString, ' ', diff), 0);
    }
  } else {
    if (isFirstSign > 0) str = myInsert1(str, firstSign, 0);
    str = myInsert1(str, intInString, 0);
  }
  return str;
}

void* myInsert1(char* src, const char* str, s21_size_t start_index) {
  for (s21_size_t i = 0; i < start_index; i++, src++)
    ;
  s21_size_t i = 0;
  for (; str[i] != '\0'; i++, src++) *src = str[i];

  return src;
}

void* myInsert2(char* src, const char* str, s21_size_t start_index) {
  int len = s21_strlen(str) + s21_strlen(src) + 1;
  char temp[len];
  char* ret = temp;

  for (s21_size_t i = 0; i < start_index; i++, ret++) *ret = src[i];

  for (s21_size_t i = 0; str[i] != '\0'; i++, ret++) *ret = str[i];

  for (s21_size_t i = start_index; src[i] != '\0'; i++, ret++) *ret = src[i];

  s21_memcpy(src, temp, len - 1);
  return src;
}

// for flags ouxX
int firstSignEnable(char spec, char* firstSign) {
  int isFirstSign = 0;
  if (spec == 'o') {
    firstSign[0] = '0';
    isFirstSign = 1;
  } else if (spec == 'X') {
    firstSign[0] = '0';
    firstSign[1] = 'X';
    isFirstSign = 2;
  } else if (spec == 'x') {
    firstSign[0] = '0';
    firstSign[1] = 'x';
    isFirstSign = 2;
  } else if (spec == 'p') {
    firstSign[0] = '0';
    firstSign[1] = 'x';
    isFirstSign = 2;
  }
  return isFirstSign;
}

unsigned long parserOUxX(char* str, flagsSprintf flags, lengthSprintf length,
                         va_list* arg, char spec) {
  char* srcStr = str;
  unsigned long decimal = 0;
  if (length.h == 1)
    decimal = (unsigned short)va_arg(*arg, unsigned);
  else if (length.l == 1 || spec == 'p')
    decimal = va_arg(*arg, unsigned long);
  else
    decimal = va_arg(*arg, unsigned);

  char firstSign[3] = "\0\0\0";
  int isFirstSign = 0;
  if (flags.sharp == 1 && (decimal != 0 || spec == 'p')) {
    isFirstSign = firstSignEnable(spec, firstSign);
  }

  int maxLen = DECIMAL100 + flags.accuracy + flags.width + 1;
  char intInString[maxLen];
  s21_memset(intInString, '\0', maxLen);

  int len = 0;

  if (spec == 'o')
    len = unsignedLongToString(decimal, intInString, 8, flags.dot);
  else if (spec == 'u')
    len = unsignedLongToString(decimal, intInString, 10, flags.dot);
  else if (spec == 'X')
    len = unsignedLongToString(decimal, intInString, 16, flags.dot);
  else {
    len = unsignedLongToString(decimal, intInString, 16, flags.dot);
    my_to_lower(intInString);
  }

  if (spec == 'o' && flags.sharp == 1) {
    flags.accuracy--;
    if (intInString[len] == '\0' && len == 0) {
      intInString[len++] = '0';
      intInString[len] = '\0';
    }
  }

  len = ifAccuracyIntMoreLen(flags, len, intInString);
  if (intInString[0] == '0' && intInString[1] == 0 && spec != 'p')
    isFirstSign = 0;

  len += isFirstSign;
  str = widthMoreLen(flags, len, intInString, str, isFirstSign, firstSign);

  *str = '\0';
  return str - srcStr;
}

int unsignedLongToString(unsigned long number, char* str, unsigned numberSystem,
                         int dot) {
  int flag = 0;
  int temp = 0;
  int i = 0;
  for (; i < 40 && flag == 0; i++) {
    if (number == 0) {
      flag = 1;
      i--;
    } else {
      temp = number % numberSystem;
      str[i] = (temp > 9) ? 55 + temp : 48 + temp;
      number /= numberSystem;
    }
  }
  if (i == 0 && dot == 0) {
    str[i] = '0';
    i++;
  }
  int len = i;
  str[len] = '\0';
  reverseString(str);
  return len;
}

// for flag id
unsigned long parserID(char* str, flagsSprintf flags, lengthSprintf length,
                       va_list* arg) {
  char* srcStr = str;
  long int decimal = 0;
  if (length.h == 1)
    decimal = (short)va_arg(*arg, int);
  else if (length.l == 1)
    decimal = va_arg(*arg, long int);
  else
    decimal = va_arg(*arg, int);

  char firstSign[2] = "\0\0";
  if (decimal < 0)
    firstSign[0] = '-';
  else if (flags.plus == 1)
    firstSign[0] = '+';
  else if (flags.space == 1)
    firstSign[0] = ' ';
  int isFirstSign = firstSign[0] == '\0' ? 0 : 1;

  if (flags.dot == 1) flags.zero = 0;

  int maxLen = DECIMAL100 + flags.accuracy + flags.width + 1;
  char intInString[maxLen];
  s21_memset(intInString, '\0', maxLen);

  int len = longToString(decimal, intInString, 10, NOT_NEED_MINUS, flags.dot);

  len = ifAccuracyIntMoreLen(flags, len, intInString);
  len += isFirstSign;

  str = widthMoreLen(flags, len, intInString, str, isFirstSign, firstSign);
  *str = '\0';
  return str - srcStr;
}

// for flags idouxX
int longToString(long int digit, char* str, unsigned numberSystem,
                 int needMinus, int dot) {
  char ifNullstr[DECIMAL100];
  if (str == s21_NULL) str = ifNullstr;

  int flag = 0;
  int minusflag = 0;
  if (digit < 0) minusflag = 1;
  int i = 0;
  int temp = 0;
  for (; i < DECIMAL100 && flag == 0; i++) {
    if (digit == 0) {
      flag = 1;
      if (i != 0)
        i--;
      else
        str[i] = '0';
    } else {
      if (minusflag == 0) {
        temp = digit % numberSystem;
        str[i] = (temp > 9) ? 55 + temp : 48 + temp;
      } else {
        temp = digit % numberSystem;
        str[i] = (temp < -9) ? 55 - temp : 48 - temp;
      }
      digit /= numberSystem;
    }
  }

  if (i == 1 && dot == 1 && str[i - 1] == '0') {
    str[--i] = '\0';
  }

  int len = i;
  if (minusflag == 1 && needMinus == 1) str[len++] = '-';
  str[len] = '\0';
  reverseString(str);
  return len;
}

// for flag c and %
unsigned long parserC(char* str, flagsSprintf flags, char ch) {
  char* srcStr = str;
  if (flags.minus == 1) {
    *str++ = ch;
    if (flags.width - 1 > 0) {
      if (flags.zero != 1)
        s21_memset(str, ' ', flags.width - 1);
      else
        s21_memset(str, '0', flags.width - 1);
      str += flags.width - 1;
    }
  } else {
    if (flags.width - 1 > 0) {
      if (flags.zero != 1)
        s21_memset(str, ' ', flags.width - 1);
      else
        s21_memset(str, '0', flags.width - 1);
      str += flags.width - 1;
    }
    *str++ = ch;
  }
  *str = '\0';
  return str - srcStr;
}

// for flag s
unsigned long parserS(char* str, flagsSprintf flags, va_list* arg) {
  char* srcStr = str;
  char* argP = va_arg(*arg, char*);
  char nullStr[7] = "(null)\0";

  if (argP == s21_NULL) {
    argP = nullStr;
  }

  int len = s21_strlen(argP);
  if (flags.accuracy < len && flags.dot == 1) len = flags.accuracy;

  char argStr[len];
  s21_strncpy(argStr, argP, len);
  argStr[len] = '\0';

  if (flags.accuracy > 0 && (s21_size_t)flags.accuracy < s21_strlen(argStr)) {
    argStr[flags.accuracy] = '\0';
    len = flags.accuracy;
  }
  if (flags.minus == 1) {
    str = myInsert1(str, argStr, 0);
    if (flags.width - len > 0) {
      s21_memset(str, ' ', flags.width - len);
      str += flags.width - len;
    }
  } else {
    if (flags.width - len > 0) {
      if (flags.zero == 0)
        s21_memset(str, ' ', flags.width - len);
      else
        s21_memset(str, '0', flags.width - len);
      str += flags.width - len;
    }
    str = myInsert1(str, argStr, 0);
  }
  *str = '\0';
  return str - srcStr;
}

// for flag f
unsigned long parserF(char* str, flagsSprintf flags, lengthSprintf length,
                      va_list* arg) {
  char* srcStr = str;
  long double decimal = 0;
  if (length.L == 1)
    decimal = va_arg(*arg, long double);
  else
    decimal = va_arg(*arg, double);

  unsigned long nanOrInf = checkNanInf(str, (long double)decimal);
  if (nanOrInf != 0) return nanOrInf;

  decimal = decimal > 0 ? decimal + EPSILON : decimal - EPSILON;

  char firstSign[2] = "\0\0";
  if (decimal + EPSILON < 0)
    firstSign[0] = '-';
  else if (flags.plus == 1)
    firstSign[0] = '+';
  else if (flags.space == 1)
    firstSign[0] = ' ';
  int isFirstSign = firstSign[0] == '\0' ? 0 : 1;

  if (flags.dot == 0 && flags.accuracy == 0) flags.accuracy = 6;

  int maxLen = DECIMAL100 + flags.accuracy + flags.width + 1;
  char intInString[maxLen];
  s21_memset(intInString, '\0', maxLen);

  decimal = roundDoubleWithAccuracy(
      decimal, (flags.accuracy +
                longToString(decimal, s21_NULL, 10, NOT_NEED_MINUS, 0)));
  int len = longDoubleToString(decimal, intInString, 10, NOT_NEED_MINUS,
                               flags.accuracy);

  if (flags.sharp == 1 && flags.accuracy == 0) {
    *(intInString + len) = '.';
    len++;
  }

  len += isFirstSign;

  str = widthMoreLen(flags, len, intInString, str, isFirstSign, firstSign);
  *str = '\0';
  return str - srcStr;
}

// for flag feEgG
int longDoubleToString(long double digit, char* str, unsigned numberSystem,
                       int needMinus, int accuracy) {
  char* srcStr = str;
  long long intDigit = (long long)digit;
  int len = longToString((long long)digit, str, numberSystem, needMinus, 0);
  if (accuracy > 0) {
    digit -= intDigit;
    for (int i = 0; i < accuracy; i++) digit *= 10;

    str += len;
    *str++ = '.';
    if (digit <= 1E-7 && digit >= -1E-7) {
      s21_memset(str, '0', accuracy);
      len += s21_strlen(str) + 1;
    } else {
      int fractionalLen =
          longToString((long long)digit, str, numberSystem, 0, 0);
      if (fractionalLen < accuracy) {
        int zeroLen = accuracy - fractionalLen;
        char zeroString[zeroLen + 1];
        zeroString[zeroLen] = '\0';
        s21_memset(zeroString, '0', zeroLen);
        myInsert2(str, zeroString, (s21_size_t)0);
        len = len + accuracy + 1;
      } else
        len = len + fractionalLen + 1;
    }
  }
  *(srcStr + len) = '\0';
  return len;
}

void removeFirstChar(char* str, char ch) {
  char tempStr[s21_strlen(str)];

  char* tempStrP = tempStr;
  char* strP = str;

  for (; *strP != ch && *strP != '\0'; strP++, tempStrP++) *tempStrP = *strP;

  if (*strP == ch) strP++;

  for (; *strP != '\0'; strP++, tempStrP++) *tempStrP = *strP;

  *tempStrP = '\0';
  s21_memcpy(str, tempStr, s21_strlen(str));
}

int checkNanInf(char* str, long double decimal) {
  char* srcStr = str;
  if (isnan(decimal)) {
    *(str++) = 'n';
    *(str++) = 'a';
    *(str++) = 'n';
    *(str) = '\0';
    return str - srcStr;
  } else if (decimal == +1.0L / 0.0L) {
    *(str++) = 'i';
    *(str++) = 'n';
    *(str++) = 'f';
    *(str) = '\0';
    return str - srcStr;
  } else if (decimal == -1.0L / 0.0L) {
    *(str++) = '-';
    *(str++) = 'i';
    *(str++) = 'n';
    *(str++) = 'f';
    *(str) = '\0';
    return str - srcStr;
  }
  return str - srcStr;
}

// for flag g
void removeEndpointsZeroforG1(char* str) {
  if (s21_strchr(str, '.') != s21_NULL) {
    for (; *str != '\0'; str++)
      ;
    int flag = 0;
    str--;
    for (; flag == 0; str--) {
      if (*str == '0')
        *str = '\0';
      else if (*str == '.') {
        *str = '\0';
        flag = 1;
      } else
        flag = 1;
    }
  }
}

void removeEndpointsZeroforG2(char* str) {
  if (s21_strchr(str, '.') != s21_NULL) {
    for (; *str != 'E'; str++)
      ;
    char* strWithExp = str;
    int flag = 0;
    str--;
    for (; flag == 0;) {
      if (*str == '0') {
        *str = '\0';
        str--;
      } else if (*str == '.') {
        *str = '\0';
        flag = 1;
        str--;
      } else
        flag = 1;
    }
    str++;
    myInsert1(str, strWithExp, 0);
    *(str + s21_strlen(strWithExp)) = '\0';
  }
}

int longDoubleGToString(long double digit, char* str, unsigned numberSystem,
                        int needMinus, int accuracy, int sharp) {
  char* srcStr = str;
  long double digitTemp = digit;
  int exp = 0;
  if (fabsl(digit) >= 1) {
    for (; fabsl(digitTemp) >= 10; exp++) digitTemp /= 10;
    if (accuracy > exp) {
      digit = roundDoubleWithAccuracy(digit, accuracy);
      int len =
          longDoubleToString(digit, str, numberSystem, 0, accuracy - exp - 1);
      if (sharp != 1)
        removeEndpointsZeroforG1(str);
      else if (accuracy - exp - 1 == 0)
        *(str + len) = '.';
    } else {
      longDoubleEToString(digit, str, numberSystem, 0, accuracy - 1, 1);
      if (sharp != 1)
        removeEndpointsZeroforG2(str);
      else if (str[1] != '.')
        myInsert2(str, ".", 1);
    }
  } else {
    char stringDouble[DECIMAL100];
    s21_memset(stringDouble, '\0', DECIMAL100);
    longDoubleToString(digit, stringDouble, numberSystem, needMinus, 16);
    removeFirstChar(stringDouble, '.');
    int accuracyForE = accuracy;
    for (int i = 0, flag = 0; i < DECIMAL100 && flag == 0; i++) {
      if (stringDouble[i] == '0')
        accuracy++;
      else
        flag = 1;
    }
    for (; fabsl(digitTemp) < 1 && fabsl(digitTemp) > EPSILON; exp++)
      digitTemp *= 10;
    if (exp > 4) {
      longDoubleEToString(digit, str, numberSystem, 0, accuracyForE - 1, 1);
      if (sharp != 1)
        removeEndpointsZeroforG2(str);
      else if (str[1] != '.')
        myInsert2(str, ".", 1);
    } else if (/*accuracy > exp ||*/ exp <= 4) {
      digit = roundDoubleWithAccuracy(digit, accuracy);
      longDoubleToString(digit, str, numberSystem, 0, accuracy - 1);
      if (sharp != 1) removeEndpointsZeroforG1(str);
    }
  }
  return s21_strlen(srcStr);
}

// for flags gGeE
unsigned long parserEeGg(char* str, flagsSprintf flags, lengthSprintf length,
                         va_list* arg, char spec) {
  char* srcStr = str;
  long double decimal = 0;
  if (length.L == 1)
    decimal = va_arg(*arg, long double);
  else
    decimal = va_arg(*arg, double);

  unsigned long nanOrInf = checkNanInf(str, (long double)decimal);
  if (nanOrInf != 0) return nanOrInf;

  char firstSign[2] = "\0\0";
  if (decimal < 0)
    firstSign[0] = '-';
  else if (flags.plus == 1)
    firstSign[0] = '+';
  else if (flags.space == 1)
    firstSign[0] = ' ';
  int isFirstSign = firstSign[0] == '\0' ? 0 : 1;

  if (flags.dot == 0 && flags.accuracy == 0) flags.accuracy = 6;

  int maxLen = DECIMAL100 + flags.accuracy + flags.width + 1;
  char intInString[maxLen];
  s21_memset(intInString, '\0', maxLen);
  int len = 0;

  if (spec == 'e' || spec == 'E')
    len = longDoubleEToString(decimal, intInString, 10, NOT_NEED_MINUS,
                              flags.accuracy, flags.dot);

  if (spec == 'g' || spec == 'G') {
    if (flags.accuracy == 0) flags.accuracy++;
    len = longDoubleGToString(decimal, intInString, 10, NOT_NEED_MINUS,
                              flags.accuracy, flags.sharp);
  }

  if (spec == 'e' || spec == 'g') my_to_lower(intInString);
  if ((spec == 'e' || spec == 'E') && flags.sharp == 1 && flags.accuracy == 0) {
    myInsert2(intInString, ".", 1);
    len++;
  }
  len += isFirstSign;
  str = widthMoreLen(flags, len, intInString, str, isFirstSign, firstSign);
  *str = '\0';
  return str - srcStr;
}

long double getNewDigit(long double digit, int accuracy, int dot) {
  if (accuracy < 1 && dot == 1)
    digit = roundDoubleWithAccuracy(digit, 1);
  else if (accuracy > 0)
    digit = roundDoubleWithAccuracy(digit, accuracy + 1);

  return digit;
}

int longDoubleEToString(long double digit, char* str, unsigned numberSystem,
                        int needMinus, int accuracy, int dot) {
  char* srcStr = str;
  if (fabsl(digit) >= 1) {
    int i = 0;
    for (; fabsl(digit) >= 10; i++) digit /= 10;
    digit = getNewDigit(digit, accuracy, dot);
    if (digit >= 10) {
      digit /= 10;
      i++;
    }
    longDoubleToString(digit, str, numberSystem, needMinus, accuracy);
    if (needMinus == 1) str++;
    if (accuracy > 0)
      str = str + accuracy + 2;
    else
      str = str + 1;
    *str++ = 'E';
    *str++ = '+';
    if (i > 9)
      str += longToString(i, str, 10, 0, 0);
    else {
      *str++ = '0';
      str += longToString(i, str, 10, 0, 0);
    }
  } else {
    int i = 0;
    for (; fabsl(digit) < 1 && fabsl(digit) > EPSILON; i++) digit *= 10;
    digit = getNewDigit(digit, accuracy, dot);
    longDoubleToString(digit, str, numberSystem, needMinus, accuracy);
    if (needMinus == 1) str++;
    if (accuracy > 0)
      str = str + accuracy + 2;
    else
      str = str + 1;
    *str++ = 'E';
    if (fabsl(digit) > EPSILON)
      *str++ = '-';
    else
      *str++ = '+';
    if (i > 9)
      str += longToString(i, str, 10, 0, 0);
    else {
      *str++ = '0';
      str += longToString(i, str, 10, 0, 0);
    }
  }
  *(str) = '\0';
  return s21_strlen(srcStr);
}

long double roundDoubleWithAccuracy(long double digit, int accuracy) {
  if (accuracy == 0) accuracy = 1;
  long double digitCopy = digit;
  digit = fabsl(digit);
  char stringIntPart[DECIMAL100];
  s21_memset(stringIntPart, '\0', DECIMAL100);
  int lenIntPart =
      longToString((long)digit, stringIntPart, 10, NOT_NEED_MINUS, 0);
  int count10 = 0;

  for (int flag = 0; count10 < 15 && flag == 0;) {
    if (floor(digit) + EPSILON > digit) flag = 1;
    digit *= 10;
    count10++;
  }
  if (accuracy < count10 + lenIntPart) {
    char stringDouble[DECIMAL100];
    s21_memset(stringDouble, '\0', DECIMAL100);
    longDoubleToString(digitCopy, stringDouble, 10, NOT_NEED_MINUS,
                       count10 + 1);
    removeFirstChar(stringDouble, '.');

    if (stringDouble[accuracy] >= '5' && stringDouble[accuracy] <= '9') {
      if (lenIntPart >= accuracy) {
        long sum = 1;
        for (int i = 0; i < lenIntPart - accuracy; i++) sum *= 10;
        digitCopy = digitCopy > 0 ? digitCopy + (long double)sum
                                  : digitCopy - (long double)sum;
      } else {
        long double sum = 1;
        for (int i = 0; i < accuracy - lenIntPart; i++) sum /= 10;
        digitCopy = digitCopy > 0 ? digitCopy + sum : digitCopy - sum;
      }
    }
  }
  return digitCopy;
}

void* my_to_lower(char* str) {
  char* srcStr = str;
  for (; *str != '\0'; str++)
    if (*str >= 65 /*'A'*/ && *str <= 90 /*'Z'*/) *str += 32;
  return srcStr;
}