#include "test.h"

// 5    Тестирование функции s21_strncat
START_TEST(s21_strncat_test01) {
  char dest[128] = {0};
  const char src1[] = "some text";
  const char src2[] = "";
  int bytes1 = sizeof(src1);
  int bytes2 = 1;
  if (_i == 0)
    ck_assert_pstr_eq(s21_strncat(dest, src1, bytes1),
                      strncat(dest, src1, bytes1));
  if (_i == 1)
    ck_assert_pstr_eq(s21_strncat(dest, src2, bytes2),
                      strncat(dest, src2, bytes2));
}
END_TEST

// 6    Тестирование функции s21_strchr
START_TEST(s21_strchr_test02) {
  const char str_test1[] = "Some string";
  const char str_test2[] = "";
  int ch_test1 = 't';
  int ch_test2 = 'Z';
  if (_i == 0)
    ck_assert_pstr_eq(s21_strchr(str_test1, ch_test1),
                      strchr(str_test1, ch_test1));
  if (_i == 1)
    ck_assert_pstr_eq(s21_strchr(str_test1, ch_test2),
                      strchr(str_test1, ch_test2));
  if (_i == 2)
    ck_assert_pstr_eq(s21_strchr(str_test2, ch_test1),
                      strchr(str_test2, ch_test1));
}
END_TEST

// 7    Тестирование функции s21_strncmp
START_TEST(s21_strncmp_test06) {
  const char str_test1[] = "Some str";
  int sz_test1 = sizeof(str_test1);
  const char str_test2[] = "";
  int sz_test2 = sizeof(str_test2);
  const char str_test3_1[] = "Some";
  const char str_test3_2[] = "Somes\0text";
  // Одинаковые строки
  if (_i == 0)
    ck_assert_int_eq(s21_strncmp(str_test1, str_test1, sz_test1),
                     strncmp(str_test1, str_test1, sz_test1));
  // Одинаковые строки нулевой длины
  if (_i == 1)
    ck_assert_int_eq(s21_strncmp(str_test2, str_test2, sz_test2),
                     strncmp(str_test2, str_test2, sz_test2));
  // Разные строки, но идентичные до \0 символа
  if (_i == 2)
    ck_assert_int_eq(s21_strncmp(str_test3_1, str_test3_2, 10),
                     strncmp(str_test3_1, str_test3_2, 10));
  // Первая строка больше второй
  if (_i == 3) ck_assert_int_gt(s21_strncmp(str_test1, str_test2, 5), 0);
  if (_i == 4) ck_assert_int_gt(strncmp(str_test1, str_test2, 5), 0);
  // Первая строка меньше второй
  if (_i == 5) ck_assert_int_lt(s21_strncmp(str_test2, str_test1, 5), 0);
  if (_i == 6) ck_assert_int_lt(strncmp(str_test2, str_test1, 5), 0);
}
END_TEST

// 8    Тестирование функции s21_strncpy
START_TEST(s21_strncpy_test03) {
  char dest1[128] = {0};
  char dest2[20] = {0};
  const char src1[] = "Another text";
  const char src2[] = "Some te\0xt";
  s21_size_t sz_test1 = sizeof(src1);
  s21_size_t sz_test2 = 20;
  if (_i == 0)
    ck_assert_pstr_eq(s21_strncpy(dest1, src1, sz_test1),
                      strncpy(dest1, src1, sz_test1));
  if (_i == 1)
    ck_assert_pstr_eq(s21_strncpy(dest1, src2, sz_test2),
                      strncpy(dest1, src2, sz_test2));
  if (_i == 2)
    ck_assert_pstr_eq(s21_strncpy(dest2, src1, sz_test1),
                      strncpy(dest2, src1, sz_test1));
  if (_i == 3)
    ck_assert_pstr_eq(s21_strncpy(dest2, src2, sz_test2),
                      strncpy(dest2, src2, sz_test2));
}
END_TEST

// 9    Тестирование функции s21_strcspn
START_TEST(s21_strcspn_test01) {
  const char str_test1[] = "This is 1st 23456 test";
  const char str_test2[] = "";
  const char rej_str[] = "e8623";
  if (_i == 0)
    ck_assert_uint_eq(strcspn(str_test1, rej_str), strcspn(str_test1, rej_str));
  if (_i == 1)
    ck_assert_uint_eq(strcspn(str_test2, rej_str), strcspn(str_test2, rej_str));
}
END_TEST

// 9.5    Тестирование функции s21_strspn
START_TEST(s21_strspn_test01) {
  const char str_test1[] = "This is 1st 23456 test";
  const char str_test2[] = "";
  const char srch_str[] = "t64";
  if (_i == 0)
    ck_assert_uint_eq(strcspn(str_test1, srch_str),
                      strcspn(str_test1, srch_str));
  if (_i == 1)
    ck_assert_uint_eq(strcspn(str_test2, srch_str),
                      strcspn(str_test2, srch_str));
}
END_TEST

// 10    Тестирование функции s21_strerror
START_TEST(s21_strerror_test03) {
  int err_test = 33;
  if (_i == 0)
    ck_assert_pstr_eq(s21_strerror(_i * err_test), strerror(_i * err_test));
  if (_i == 1)
    ck_assert_pstr_eq(s21_strerror(_i * err_test), strerror(_i * err_test));
  if (_i == 2)
    ck_assert_pstr_eq(s21_strerror(_i * err_test), strerror(_i * err_test));
  if (_i == 3) ck_assert_pstr_eq(s21_strerror(200), strerror(200));
}
END_TEST

// 11    Тестирование функции s21_strlen
START_TEST(s21_strlen_test02) {
  const char str_test1[] = "Some test string";
  const char str_test2[] = "Some test \5string";
  const char str_test3[] = "\0";
  if (_i == 0) ck_assert_uint_eq(s21_strlen(str_test1), strlen(str_test1));
  if (_i == 1) ck_assert_uint_eq(s21_strlen(str_test2), strlen(str_test2));
  if (_i == 2) ck_assert_uint_eq(s21_strlen(str_test3), strlen(str_test3));
}
END_TEST

// 12    Тестирование функции s21_strpbrk
START_TEST(s21_strpbrk_test02) {
  const char str_test1[] = "Another text";
  const char str_test2[] = "";
  const char acc_test1[] = "xo";
  const char acc_test2[] = "";
  if (_i == 0)
    ck_assert_pstr_eq(s21_strpbrk(str_test1, acc_test1),
                      strpbrk(str_test1, acc_test1));
  if (_i == 1)
    ck_assert_pstr_eq(s21_strpbrk(str_test1, acc_test2),
                      strpbrk(str_test1, acc_test2));
  if (_i == 2)
    ck_assert_pstr_eq(s21_strpbrk(str_test2, acc_test1),
                      strpbrk(str_test2, acc_test1));
}
END_TEST

// 13    Тестирование функции s21_strrchr
START_TEST(s21_strrchr_test04) {
  const char str_test1[] = "Another text";
  const char str_test2[] = "";
  int ch_test1 = 'e';
  int ch_test2 = '\0';
  int ch_test3 = 'z';
  if (_i == 0)
    ck_assert_pstr_eq(s21_strrchr(str_test1, ch_test1),
                      strrchr(str_test1, ch_test1));
  if (_i == 1)
    // Поиск должен идти по нулевому символу в том числе
    ck_assert_pstr_eq(s21_strrchr(str_test1, ch_test2),
                      strrchr(str_test1, ch_test2));
  if (_i == 2)
    ck_assert_pstr_eq(s21_strrchr(str_test2, ch_test1),
                      strrchr(str_test2, ch_test1));
  if (_i == 3)
    ck_assert_pstr_eq(s21_strrchr(str_test2, ch_test2),
                      strrchr(str_test2, ch_test2));
  if (_i == 4)
    ck_assert_pstr_eq(s21_strrchr(str_test1, ch_test3),
                      strrchr(str_test1, ch_test3));
}
END_TEST

// 14    Тестирование функции s21_strstr
START_TEST(s21_strstr_test02) {
  const char str1_test1[] = "Another text";
  const char str2_test1[] = "";
  const char str1_test2[] = "";
  const char str2_test2[] = "test";
  const char str1_test3[] = "Some test string";
  const char str2_test3[] = "test";
  if (_i == 0)
    ck_assert_pstr_eq(s21_strstr(str1_test1, str2_test1),
                      strstr(str1_test1, str2_test1));
  if (_i == 1)
    ck_assert_pstr_eq(s21_strstr(str1_test2, str2_test2),
                      strstr(str1_test2, str2_test2));
  if (_i == 2)
    ck_assert_pstr_eq(s21_strstr(str1_test3, str2_test3),
                      strstr(str1_test3, str2_test3));
}
END_TEST

// 15    Тестирование функции s21_strtok
START_TEST(s21_strtok_test02) {  // почему везде тест с NULL????
  char str1_test1[] = "Text, moe, one";
  char str2_test1[] = "Text, moe, one";
  char str1_test2[] = "\0Text,moe,one";
  char str2_test2[] = "\0Text,moe,one";
  char str1_test3[] = "Text.moe\0one";
  char str2_test3[] = "Text.moe\0one";
  char str1_test4[] = " ,";
  char str2_test4[] = " ,";
  const char delim[] = " ,";
  if (_i == 0) {
    ck_assert_pstr_eq(s21_strtok(str1_test1, delim), strtok(str2_test1, delim));
    ck_assert_pstr_eq(s21_strtok(s21_NULL, delim), strtok(NULL, delim));
    ck_assert_pstr_eq(s21_strtok(s21_NULL, delim), strtok(NULL, delim));
  }
  if (_i == 1) {
    ck_assert_pstr_eq(s21_strtok(str1_test2, delim), strtok(str2_test2, delim));
    ck_assert_pstr_eq(s21_strtok(s21_NULL, delim), strtok(NULL, delim));
  }
  if (_i == 2) {
    ck_assert_pstr_eq(s21_strtok(str1_test4, delim), strtok(str2_test4, delim));
    ck_assert_pstr_eq(s21_strtok(s21_NULL, delim), strtok(NULL, delim));
  }
  if (_i == 3) {
    ck_assert_pstr_eq(s21_strtok(str1_test3, delim), strtok(str2_test3, delim));
    ck_assert_pstr_eq(s21_strtok(s21_NULL, delim), strtok(NULL, delim));
  }
}
END_TEST

Suite *suite_string_create(void) {
  Suite *suite = suite_create("\n-- S21_STRING functions tests --");
  TCase *str_func_tests = tcase_create("\n- s21_string test cases");

  tcase_add_loop_test(str_func_tests, s21_strncat_test01, 0, 2);
  tcase_add_loop_test(str_func_tests, s21_strchr_test02, 0, 3);
  tcase_add_loop_test(str_func_tests, s21_strncmp_test06, 0, 7);
  tcase_add_loop_test(str_func_tests, s21_strncpy_test03, 0, 4);
  tcase_add_loop_test(str_func_tests, s21_strcspn_test01, 0, 2);
  tcase_add_loop_test(str_func_tests, s21_strspn_test01, 0, 2);
  tcase_add_loop_test(str_func_tests, s21_strerror_test03, 0, 4);
  tcase_add_loop_test(str_func_tests, s21_strlen_test02, 0, 3);
  tcase_add_loop_test(str_func_tests, s21_strpbrk_test02, 0, 3);
  tcase_add_loop_test(str_func_tests, s21_strrchr_test04, 0, 5);
  tcase_add_loop_test(str_func_tests, s21_strstr_test02, 0, 3);
  tcase_add_loop_test(str_func_tests, s21_strtok_test02, 0, 4);

  // Добавление групп тестов в набор
  suite_add_tcase(suite, str_func_tests);

  return suite;
}