#include "test.h"

// 20    Тестирование функции s21_sprintf d флаг
START_TEST(s21_sprintf_d_test08) {
  char str1[128] = {0};
  char str2[128] = {0};
  char *formats[5] = {"%-9.14d", "%+9.7d", "% 9.7hd", "%014.7ld", "%0.hd"};
  int vals[5] = {7234234, -12409895, 4768939, -000002101, 0000};

  if (_i >= 0 && _i < 5) {
    ck_assert_int_eq(sprintf(str1, formats[_i], vals[_i]),
                     s21_sprintf(str2, formats[_i], vals[_i]));
  }
  if (_i == 5) {
    ck_assert_int_eq(sprintf(str1, "\033[43m%+*.7d\033[0m", 10, -4),
                     s21_sprintf(str2, "\033[43m%+*.7d\033[0m", 10, -4));
  }
  if (_i == 6) {
    ck_assert_int_eq(sprintf(str1, "% -*.*d", 10, 120, 2147483647),
                     s21_sprintf(str2, "% -*.*d", 10, 120, 2147483647));
  }
  if (_i == 7) {
    ck_assert_int_eq(
        sprintf(str1, "% -*.*d plus %+.hd", 10, 110, -2147483647, 012300),
        s21_sprintf(str2, "% -*.*d plus %+.hd", 10, 110, -2147483647, 012300));
  }
  if (_i == 8) {
    ck_assert_int_eq(
        sprintf(str1, "% -*.*d plus %+.*hd", 0, 0, 2147483647, 10, 012300),
        s21_sprintf(str2, "% -*.*d plus %+.*hd", 0, 0, 2147483647, 10, 012300));
  }
  ck_assert_str_eq(str1, str2);
}
END_TEST

// 21    Тестирование функции s21_sprintf f флаг
START_TEST(s21_sprintf_f_test08) {
  char str1[256] = {0};
  char str2[256] = {0};

  if (_i == 0) {
    sprintf(str1, "%-9.14f", 7234234.678);
    s21_sprintf(str2, "%-9.14f", 7234234.678);
  }
  if (_i == 1) {
    sprintf(str1, "%+9.7f", 12409895.1234567891);
    s21_sprintf(str2, "%+9.7f", 12409895.1234567891);
  }
  if (_i == 2) {
    sprintf(str1, "%014.7lf", 4768939.);
    s21_sprintf(str2, "%014.7lf", 4768939.);
  }
  if (_i == 3) {
    sprintf(str1, "\033[42m%0.f\033[0m", 0000.000);
    s21_sprintf(str2, "\033[42m%0.f\033[0m", 0000.000);
  }
  if (_i == 4) {
    long double val = 000002101.123456789123456789123456789123456789;
    sprintf(str1, "% 9.7Lf", val);
    s21_sprintf(str2, "% 9.7Lf", val);
  }
  if (_i == 5) {
    sprintf(str1, "%+*.7f", 10, 2.0);
    s21_sprintf(str2, "%+*.7f", 10, 2.0);
  }
  if (_i == 6) {
    sprintf(str1, "\n\033[42m% -*.*f %%%%\033[0m\n", 9, 10, 214748.123456789);
    s21_sprintf(str2, "\n\033[42m% -*.*f %%%%\033[0m\n", 9, 10,
                214748.123456789);
  }
  if (_i == 7) {
    double val1 = 123456789.123456789;
    double val2 = 012300.878333335;
    sprintf(str1, "\n\033[42m% -#*.*f plus %+.lf\033[0m\n", 10, 12, val1, val2);
    s21_sprintf(str2, "\n\033[42m% -#*.*f plus %+.lf\033[0m\n", 10, 12, val1,
                val2);
  }
  if (_i == 8) {
    long double val1 = 1234567892147483647.123456789;
    double val2 = 012300.878333335;
    sprintf(str1, "% -*.*Lf plus %+.*lf", 0, 0, val1, 10, val2);
    s21_sprintf(str2, "% -*.*Lf plus %+.*lf", 0, 0, val1, 10, val2);
  }
  if (_i == 9) {
    sprintf(str1, "%+*.7f, %#5.f", 10, -2.0, 1234567.89);
    s21_sprintf(str2, "%+*.7f, %#5.f", 10, -2.0, 1234567.89);
  }
  if (_i == 10) {
    sprintf(str1, "%f, %f, %f", INFINITY, -INFINITY, NAN);
    s21_sprintf(str2, "%f, %f, %f", INFINITY, -INFINITY, NAN);
  }
  ck_assert_str_eq(str1, str2);
}
END_TEST

// 22    Тестирование функции s21_sprintf u флаг
START_TEST(s21_sprintf_u_test08) {
  char str1[256] = {0};
  char str2[256] = {0};

  if (_i == 0) {
    ck_assert_int_eq(sprintf(str1, "%-9.14u", 7234234),
                     s21_sprintf(str2, "%-9.14u", 7234234));
  }
  if (_i == 1) {
    ck_assert_int_eq(sprintf(str1, "%27u", -2409895),
                     s21_sprintf(str2, "%27u", -2409895));
  }
  if (_i == 2) {
    ck_assert_int_eq(sprintf(str1, "%9.7hu", 4768939),
                     s21_sprintf(str2, "%9.7hu", 4768939));
  }
  if (_i == 3) {
    ck_assert_int_eq(sprintf(str1, "%14.03lu", 2101123456789123),
                     s21_sprintf(str2, "%14.03lu", 2101123456789123));
  }
  if (_i == 4) {
    ck_assert_int_eq(sprintf(str1, "%3.hu", 0000),
                     s21_sprintf(str2, "%3.hu", 0000));
  }
  if (_i == 5) {
    ck_assert_int_eq(sprintf(str1, "%*.7u", 10, 4),
                     s21_sprintf(str2, "%*.7u", 10, 4));
  }
  if (_i == 6) {
    ck_assert_int_eq(sprintf(str1, "%-*.*u", 10, 120, 2147483647),
                     s21_sprintf(str2, "%-*.*u", 10, 120, 2147483647));
  }
  if (_i == 7) {
    ck_assert_int_eq(
        sprintf(str1, "%-*.*u plus %.hu", 10, 110, 2147483647, 012300),
        s21_sprintf(str2, "%-*.*u plus %.hu", 10, 110, 2147483647, 012300));
  }
  if (_i == 8) {
    ck_assert_int_eq(sprintf(str1, "%-*.*lu plus %.*hu", 0, 0,
                             2147483647123456789, 10, 012300),
                     s21_sprintf(str2, "%-*.*lu plus %.*hu", 0, 0,
                                 2147483647123456789, 10, 012300));
  }
  ck_assert_str_eq(str1, str2);
}
END_TEST

// 23    Тестирование функции s21_sprintf g/G флаг
START_TEST(s21_sprintf_g_test08) {
  char str1[256] = {0};
  char str2[256] = {0};

  if (_i == 0) {
    sprintf(str1, "%-9.4g", 7234234.67812345);
    s21_sprintf(str2, "%-9.4g", 7234234.67812345);
  }
  if (_i == 1) {
    sprintf(str1, "%+#9.0G", -12409895.01234567891);
    s21_sprintf(str2, "%+#9.0G", -12409895.01234567891);
  }
  if (_i == 2) {
    sprintf(str1, "%014.7lg", 4768939.);
    s21_sprintf(str2, "%014.7lg", 4768939.);
  }
  if (_i == 3) {
    sprintf(str1, "%+0.G", 0000.000);
    s21_sprintf(str2, "%+0.G", 0000.000);
  }
  if (_i == 4) {
    long double val = 000002101.123456789123456789123456789123456789;
    sprintf(str1, "% 9.7LG", val);
    s21_sprintf(str2, "% 9.7LG", val);
  }
  if (_i == 5) {
    sprintf(str1, "%+*.7g", 10, 2.0);
    s21_sprintf(str2, "%+*.7g", 10, 2.0);
  }
  if (_i == 6) {
    sprintf(str1, "\n% -#*.*G %%%%\n", 01, 20, 214748.123456789);
    s21_sprintf(str2, "\n% -#*.*G %%%%\n", 01, 20, 214748.123456789);
  }
  if (_i == 7) {
    double val1 = 123456789.123456789;
    double val2 = 012300.878333335;
    sprintf(str1, "\n\033[46m% -#*.*G plus %+.lg\033[0m\n", 10, 12, val1, val2);
    s21_sprintf(str2, "\n\033[46m% -#*.*G plus %+.lg\033[0m\n", 10, 12, val1,
                val2);
  }
  if (_i == 8) {
    long double val1 = 1234567892147483647.123456789;
    double val2 = 012300.878333335;
    sprintf(str1, "% -*.*Lg plus %+0.*lg", 0, 0, val1, 10, val2);
    s21_sprintf(str2, "% -*.*Lg plus %+0.*lg", 0, 0, val1, 10, val2);
  }
  ck_assert_str_eq(str1, str2);
}
END_TEST

// 24    Тестирование функции s21_sprintf e/E флаг
START_TEST(s21_sprintf_e_test08) {
  char str1[256] = {0};
  char str2[256] = {0};

  if (_i == 0) {
    sprintf(str1, "\033[44m%-9.4e\033[0m", 7234234.67812345);
    s21_sprintf(str2, "\033[44m%-9.4e\033[0m", 7234234.67812345);
  }
  if (_i == 1) {
    sprintf(str1, "\033[44m%+#9.9E\033[0m", 12409895.01234567891);
    s21_sprintf(str2, "\033[44m%+#9.9E\033[0m", 12409895.01234567891);
  }
  if (_i == 2) {
    sprintf(str1, "\033[44m%014.7le\033[0m", -4768939.);
    s21_sprintf(str2, "\033[44m%014.7le\033[0m", -4768939.);
  }
  if (_i == 3) {
    sprintf(str1, "\033[44m%+0.E\033[0m", 0000.000);
    s21_sprintf(str2, "\033[44m%+0.E\033[0m", 0000.000);
  }
  if (_i == 4) {
    long double val = -000002101.123456789123456789123456789123456789;
    sprintf(str1, "\033[44m% 9.7LE\033[0m", val);
    s21_sprintf(str2, "\033[44m% 9.7LE\033[0m", val);
  }
  if (_i == 5) {
    sprintf(str1, "\033[44m%+*.7e\033[0m", 10, 2.0);
    s21_sprintf(str2, "\033[44m%+*.7e\033[0m", 10, 2.0);
  }
  if (_i == 6) {
    sprintf(str1, "\n\033[44m% -#*.*E %%%%\033[0m\n", 01, 15, 214748.123456789);
    s21_sprintf(str2, "\n\033[44m% -#*.*E %%%%\033[0m\n", 01, 15,
                214748.123456789);
  }
  if (_i == 7) {
    double val1 = 123456789.123456789;
    long double val2 = 012300.878333335;
    sprintf(str1, "\n\033[44m% #0*.*e plus %+.LE\033[0m\n", 15, 8, val1, val2);
    s21_sprintf(str2, "\n\033[44m% #0*.*e plus %+.LE\033[0m\n", 10, 8, val1,
                val2);
  }
  if (_i == 8) {
    long double val1 = 1234567892147483647.123456789;
    double val2 = 012300.878333335;
    sprintf(str1, "\033[44m% -*.*Le plus %+0.*lE\033[0m", 0, 0, val1, 10, val2);
    s21_sprintf(str2, "\033[44m% -*.*Le plus %+0.*lE\033[0m", 0, 0, val1, 10,
                val2);
  }
  if (_i == 9) {
    sprintf(str1, "%e, %e, %e", INFINITY, -INFINITY, NAN);
    s21_sprintf(str2, "%e, %e, %e", INFINITY, -INFINITY, NAN);
  }
  ck_assert_str_eq(str1, str2);
}
END_TEST

// 25    Тестирование функции s21_sprintf x/X флаг
START_TEST(s21_sprintf_x_test08) {
  char str1[256] = {0};
  char str2[256] = {0};

  if (_i == 0) {
    ck_assert_int_eq(sprintf(str1, "\033[43m%-9.14x\033[0m", 0XFEF1),
                     s21_sprintf(str2, "\033[43m%-9.14x\033[0m", 0XFEF1));
  }
  if (_i == 1) {
    ck_assert_int_eq(sprintf(str1, "\033[43m%27x\033[0m", -2409895),
                     s21_sprintf(str2, "\033[43m%27x\033[0m", -2409895));
  }
  if (_i == 2) {
    ck_assert_int_eq(sprintf(str1, "\033[43m%9.7hX\033[0m", 4768939),
                     s21_sprintf(str2, "\033[43m%9.7hX\033[0m", 4768939));
  }
  if (_i == 3) {
    ck_assert_int_eq(
        sprintf(str1, "\033[43m%14.03lX\033[0m", 0x1AC4F113AD),
        s21_sprintf(str2, "\033[43m%14.03lX\033[0m", 0x1AC4F113AD));
  }
  if (_i == 4) {
    ck_assert_int_eq(
        sprintf(str1, "\033[43m%#3.hX here is hex\033[0m", 0000),
        s21_sprintf(str2, "\033[43m%#3.hX here is hex\033[0m", 0000));
  }
  if (_i == 5) {
    ck_assert_int_eq(
        sprintf(str1, "\033[43m\\some text! %#*.7x\033[0m", 10, 0XFFFADE12),
        s21_sprintf(str2, "\033[43m\\some text! %#*.7x\033[0m", 10,
                    0XFFFADE12));
  }
  if (_i == 6) {
    ck_assert_int_eq(
        sprintf(str1, "\033[43m%-*.*X\033[0m", 10, 120, 2147483647),
        s21_sprintf(str2, "\033[43m%-*.*X\033[0m", 10, 120, 2147483647));
  }
  if (_i == 7) {
    ck_assert_int_eq(sprintf(str1, "\033[43m%-*.*x plus %.hX\033[0m", 10, 110,
                             2147483647, 0x0ad3f),
                     s21_sprintf(str2, "\033[43m%-*.*x plus %.hX\033[0m", 10,
                                 110, 2147483647, 0x0ad3f));
  }
  if (_i == 8) {
    ck_assert_int_eq(sprintf(str1, "\033[43m%-#*.*lX plus %.*hx\033[0m", 0, 0,
                             2147483647123456789, 10, 012300),
                     s21_sprintf(str2, "\033[43m%-#*.*lX plus %.*hx\033[0m", 0,
                                 0, 2147483647123456789, 10, 012300));
  }
  ck_assert_str_eq(str1, str2);
}
END_TEST

// 26    Тестирование функции s21_sprintf o флаг
START_TEST(s21_sprintf_o_test08) {
  char str1[256] = {0};
  char str2[256] = {0};

  if (_i == 0) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%-9.14o\033[0m", 1234444731),
                     s21_sprintf(str2, "\033[45m%-9.14o\033[0m", 1234444731));
  }
  if (_i == 1) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%27o\033[0m", -2403215),
                     s21_sprintf(str2, "\033[45m%27o\033[0m", -2403215));
  }
  if (_i == 2) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%15.7ho\033[0m", 7612415),
                     s21_sprintf(str2, "\033[45m%15.7ho\033[0m", 7612415));
  }
  if (_i == 3) {
    ck_assert_int_eq(
        sprintf(str1, "\033[45m%14.03lo\033[0m", 12356541526417),
        s21_sprintf(str2, "\033[45m%14.03lo\033[0m", 12356541526417));
  }
  if (_i == 4) {
    ck_assert_int_eq(
        sprintf(str1, "\033[45m%#3.ho here is octal\033[0m", 0000),
        s21_sprintf(str2, "\033[45m%#3.ho here is octal\033[0m", 0000));
  }
  if (_i == 5) {
    ck_assert_int_eq(
        sprintf(str1, "\033[45m\\some text! %#*.7o\033[0m", 10, 777777777),
        s21_sprintf(str2, "\033[45m\\some text! %#*.7o\033[0m", 10, 777777777));
  }
  if (_i == 6) {
    ck_assert_int_eq(
        sprintf(str1, "\033[45m%-*.*o\033[0m", 10, 120, 2147403647),
        s21_sprintf(str2, "\033[45m%-*.*o\033[0m", 10, 120, 2147403647));
  }
  if (_i == 7) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%-*.*o plus %.ho\033[0m", 10, 110,
                             2147423647, 67123),
                     s21_sprintf(str2, "\033[45m%-*.*o plus %.ho\033[0m", 10,
                                 110, 2147423647, 67123));
  }
  if (_i == 8) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%-#*.*lo plus %.*ho\033[0m", 0, 0,
                             2147483647123456789, 10, 012300),
                     s21_sprintf(str2, "\033[45m%-#*.*lo plus %.*ho\033[0m", 0,
                                 0, 2147483647123456789, 10, 012300));
  }
  ck_assert_str_eq(str1, str2);
}
END_TEST

// 26    Тестирование функции s21_sprintf p флаг
START_TEST(s21_sprintf_p_test08) {
  char str1[256] = {0};
  char str2[256] = {0};
  long int a = 1111352352352;
  long int *ch = &a;
  char *ch2 = "str";
  int *p = (int *)str1;

  if (_i == 0) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%-9p\033[0m", &a),
                     s21_sprintf(str2, "\033[45m%-9p\033[0m", &a));
  }
  if (_i == 1) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%27p\033[0m", &a),
                     s21_sprintf(str2, "\033[45m%27p\033[0m", &a));
  }
  if (_i == 2) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%15p\033[0m", &a),
                     s21_sprintf(str2, "\033[45m%15p\033[0m", &a));
  }
  if (_i == 3) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%14p\033[0m", ch),
                     s21_sprintf(str2, "\033[45m%14p\033[0m", ch));
  }
  if (_i == 4) {
    ck_assert_int_eq(
        sprintf(str1, "\033[45m%p here is pointer\033[0m", &a),
        s21_sprintf(str2, "\033[45m%p here is pointer\033[0m", &a));
  }
  if (_i == 5) {
    ck_assert_int_eq(
        sprintf(str1, "\033[45m\\some text! %*p\033[0m", 10, p),
        s21_sprintf(str2, "\033[45m\\some text! %*p\033[0m", 10, p));
  }
  if (_i == 6) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%-*p\033[0m", 10, ch2),
                     s21_sprintf(str2, "\033[45m%-*p\033[0m", 10, ch2));
  }
  if (_i == 7) {
    ck_assert_int_eq(sprintf(str1, "%-*p plus %p", 10, &a, p),
                     s21_sprintf(str2, "%-*p plus %p", 10, &a, p));
  }
  if (_i == 8) {
    ck_assert_int_eq(sprintf(str1, "%-*p plus %p", 0, ch, ch2),
                     s21_sprintf(str2, "%-*p plus %p", 0, ch, ch2));
  }
  ck_assert_str_eq(str1, str2);
}
END_TEST

// 27    Тестирование функции s21_sprintf c флаг
START_TEST(s21_sprintf_c_test06) {
  char str1[256] = {0};
  char str2[256] = {0};
  int val1 = 114;
  int val2 = 127;
  int val3 = 221;
  char ch = '\0';
  char ch2 = ' ';

  if (_i == 0) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%-9c\033[0m", val1),
                     s21_sprintf(str2, "\033[45m%-9c\033[0m", val1));
  }
  if (_i == 1) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%27lc\033[0m", val2),
                     s21_sprintf(str2, "\033[45m%27lc\033[0m", val2));
  }
  if (_i == 2) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%15c\033[0m", ch),
                     s21_sprintf(str2, "\033[45m%15c\033[0m", ch));
  }
  if (_i == 3) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%14c %-2c\033[0m", ch, val2),
                     s21_sprintf(str2, "\033[45m%14c %-2c\033[0m", ch, val2));
  }
  if (_i == 4) {
    ck_assert_int_eq(
        sprintf(str1, "\033[45m\\some text! %*c\033[0m", 10, val3),
        s21_sprintf(str2, "\033[45m\\some text! %*c\033[0m", 10, val3));
  }
  if (_i == 5) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%-*c\033[0m", 10, ch2),
                     s21_sprintf(str2, "\033[45m%-*c\033[0m", 10, ch2));
  }
  if (_i == 6) {
    ck_assert_int_eq(sprintf(str1, "%-*c plus %c", 10, ch2, val3),
                     s21_sprintf(str2, "%-*c plus %c", 10, ch2, val3));
  }
  if (_i == 7) {
    ck_assert_int_eq(sprintf(str1, "%10c plus %-10c", ch2, val3),
                     s21_sprintf(str2, "%10c plus %-10c", ch2, val3));
  }
  ck_assert_str_eq(str1, str2);
}
END_TEST

// 28    Тестирование функции s21_sprintf s флаг
START_TEST(s21_sprintf_s_test06) {
  char str1[256] = {0};
  char str2[256] = {0};
  char *tstr1 = "some text";
  char *tstr2 = "test\0here";
  char *tstr3 = "\0";
  char *tstr4 = "-+0=%&\\\\";
  char *tstr5 = s21_NULL;

  if (_i == 0) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%-9s\033[0m", tstr1),
                     s21_sprintf(str2, "\033[45m%-9s\033[0m", tstr1));
  }
  if (_i == 1) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%1s\033[0m", tstr2),
                     s21_sprintf(str2, "\033[45m%1s\033[0m", tstr2));
  }
  if (_i == 2) {
    ck_assert_int_eq(sprintf(str1, "\033[45m%15s\033[0m", tstr3),
                     s21_sprintf(str2, "\033[45m%15s\033[0m", tstr3));
  }
  if (_i == 3) {
    ck_assert_int_eq(
        sprintf(str1, "\033[45m%14s %-2s\033[0m", tstr4, tstr5),
        s21_sprintf(str2, "\033[45m%14s %-2s\033[0m", tstr4, tstr5));
  }
  if (_i == 4) {
    ck_assert_int_eq(
        sprintf(str1, "\033[45m\\some text! %*s\033[0m", 10, tstr2),
        s21_sprintf(str2, "\033[45m\\some text! %*s\033[0m", 10, tstr2));
  }
  if (_i == 5) {
    ck_assert_int_eq(sprintf(str1, "%-*s plus %s", 10, tstr4, tstr1),
                     s21_sprintf(str2, "%-*s plus %s", 10, tstr4, tstr1));
  }
  if (_i == 6) {
    ck_assert_int_eq(sprintf(str1, "%-5s plus %10s", tstr4, tstr1),
                     s21_sprintf(str2, "%-5s plus %10s", tstr4, tstr1));
  }
  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite *suite_sprintf_create(void) {
  Suite *suite = suite_create("\n-- S21_SPRINTF tests --");
  TCase *sprintf_tests = tcase_create("\n- s21_sprintf test cases");

  // Добавление тестов в 1 группу тестов
  tcase_add_loop_test(sprintf_tests, s21_sprintf_d_test08, 0, 9);
  tcase_add_loop_test(sprintf_tests, s21_sprintf_f_test08, 0, 11);
  tcase_add_loop_test(sprintf_tests, s21_sprintf_u_test08, 0, 9);
  tcase_add_loop_test(sprintf_tests, s21_sprintf_g_test08, 0, 9);
  tcase_add_loop_test(sprintf_tests, s21_sprintf_e_test08, 0, 10);
  tcase_add_loop_test(sprintf_tests, s21_sprintf_x_test08, 0, 9);
  tcase_add_loop_test(sprintf_tests, s21_sprintf_o_test08, 0, 9);
  tcase_add_loop_test(sprintf_tests, s21_sprintf_p_test08, 0, 9);
  tcase_add_loop_test(sprintf_tests, s21_sprintf_c_test06, 0, 8);
  tcase_add_loop_test(sprintf_tests, s21_sprintf_s_test06, 0, 7);

  suite_add_tcase(suite, sprintf_tests);

  return suite;
}