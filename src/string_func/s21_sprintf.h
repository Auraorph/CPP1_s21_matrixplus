#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H
#include <math.h>
#include <stdarg.h>
#include <stdio.h>

#include "../s21_string.h"

#define DECIMAL100 100
#define NEED_MINUS 1
#define NOT_NEED_MINUS 0
#define EPSILON 1e-16

typedef struct {
  int minus;  //выравнивание по левому краю
  int plus;   //явно указывается плюс или минус
  int space;  //если знак не будет выведен, перед значением вставляется пробел
  int sharp;
  int zero;  //заполняет нулями число слева, если позволяет спецификатор ширины
  int width;  //минимальное количнство печатаемых символов
  int dot;
  int accuracy;
  char length;

} flagsSprintf;

typedef struct {
  int h;
  int l;
  int L;
} lengthSprintf;

// for sprintf   BEGIN
int s21_sprintf(char* str, const char* format, ...);
int singleArgToStrint(char* str, char* srcStr, const char* format, int i,
                      va_list* arg, unsigned long* j);
int check1Flags(const char* format, flagsSprintf* flags);
int check2WidthOrAccuracy(const char* format, int* number, va_list* arg);
int stringToInt(const char* str);
int check3Length(char* str, lengthSprintf* length);
unsigned long parserHub(char* str, char* srcStr, char spec, flagsSprintf flags,
                        lengthSprintf length, va_list* arg);

void reverseString(char* str);

// for flags dieEfgGouxX
int ifAccuracyIntMoreLen(flagsSprintf flags, int len, char* intInString);
char* widthMoreLen(flagsSprintf flags, int len, char* intInString, char* str,
                   int isFirstSign, char* firstSign);
void* myInsert1(char* src, const char* str, s21_size_t start_index);
void* myInsert2(char* src, const char* str, s21_size_t start_index);

// for flags ouxX
unsigned long parserOUxX(char* str, flagsSprintf flags, lengthSprintf length,
                         va_list* arg, char spec);
int unsignedLongToString(unsigned long number, char* str, unsigned numberSystem,
                         int dot);

// for flag id
unsigned long parserID(char* str, flagsSprintf flags, lengthSprintf length,
                       va_list* arg);

// for flags idouxX
int longToString(long int digit, char* str, unsigned numberSystem,
                 int needMinus, int dot);

// for flag c and %
unsigned long parserC(char* str, flagsSprintf flags, char ch);

// for flag s
unsigned long parserS(char* str, flagsSprintf flags, va_list* arg);

// for flag f
unsigned long parserF(char* str, flagsSprintf flags, lengthSprintf length,
                      va_list* arg);

// for flag feEgG
int longDoubleToString(long double digit, char* str, unsigned numberSystem,
                       int needMinus, int accuracy);
void removeFirstChar(
    char* str, char ch);  //удаляю первое вхождение символа и в конце ставлю 0
int checkNanInf(char* str, long double decimal);

// for flag g
void removeEndpointsZeroforG1(char* str);
void removeEndpointsZeroforG2(char* str);
int longDoubleGToString(long double digit, char* str, unsigned numberSystem,
                        int needMinus, int accuracy, int sharp);

// for flags gGeE
unsigned long parserEeGg(char* str, flagsSprintf flags, lengthSprintf length,
                         va_list* arg, char spec);
int longDoubleEToString(long double digit, char* str, unsigned numberSystem,
                        int needMinus, int accuracy, int dot);
long double roundDoubleWithAccuracy(long double digit, int accuracy);
void* my_to_lower(char* str);  // E -> e, G -> g
// for sprintf   END

#endif
