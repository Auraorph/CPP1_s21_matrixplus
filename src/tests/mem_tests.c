#include "test.h"

// 1    Тестирование функции s21_memchr
START_TEST(s21_memchr_test04) {
  const char str_test1[] = "Some string";
  const char str_test2[] = "";
  int ch_test1 = 't';
  int ch_test2 = 'Z';
  s21_size_t sz_test1 = 6;
  s21_size_t sz_test2 = 512;
  s21_size_t sz_test3 = 0;
  if (_i == 0)
    ck_assert_pstr_eq(s21_memchr(str_test1, ch_test1, sz_test1),
                      memchr(str_test1, ch_test1, sz_test1));
  if (_i == 1)
    ck_assert_pstr_eq(s21_memchr(str_test1, ch_test2, sz_test1),
                      memchr(str_test1, ch_test2, sz_test1));
  if (_i == 2)
    ck_assert_pstr_eq(s21_memchr(str_test2, ch_test1, sz_test1),
                      memchr(str_test2, ch_test1, sz_test1));
  if (_i == 3)
    ck_assert_pstr_eq(s21_memchr(str_test2, ch_test1, sz_test2),
                      memchr(str_test2, ch_test1, sz_test2));
  if (_i == 4)
    ck_assert_pstr_eq(s21_memchr(str_test1, ch_test1, sz_test3),
                      memchr(str_test1, ch_test1, sz_test3));
}
END_TEST

// 2    Тестирование функции s21_memcmp
START_TEST(s21_memcmp_test05) {
  const char str_test1[] = "Some str";
  const char str_test2[] = "Some";
  const char str_test3[] = "";
  // Одинаковые строки
  if (_i == 0)
    ck_assert_int_eq(s21_memcmp(str_test1, str_test1, 5),
                     memcmp(str_test1, str_test1, 5));
  // Одинаковые строки нулевой длины
  if (_i == 1)
    ck_assert_int_eq(s21_memcmp(str_test3, str_test3, 5),
                     memcmp(str_test3, str_test3, 5));
  // Первая строка больше второй
  if (_i == 2) ck_assert_int_gt(s21_memcmp(str_test1, str_test2, 5), 0);
  if (_i == 3) ck_assert_int_gt(memcmp(str_test1, str_test2, 5), 0);
  // Первая строка меньше второй
  if (_i == 4) ck_assert_int_lt(s21_memcmp(str_test2, str_test1, 5), 0);
  if (_i == 5) ck_assert_int_lt(memcmp(str_test2, str_test1, 5), 0);
}
END_TEST

// 3    Тестирование функции s21_memcpy
START_TEST(s21_memcpy_test02) {
  char dest1[128] = {0};
  char dest2[5] = {0};
  const char src[] = "Another text";
  s21_size_t sz_test1 = sizeof(src);
  s21_size_t sz_test2 = 30;
  if (_i == 0)
    ck_assert_pstr_eq(s21_memcpy(dest1, src, sz_test1),
                      memcpy(dest1, src, sz_test1));
  if (_i == 1)
    ck_assert_pstr_eq(s21_memcpy(dest1, src, sz_test2),
                      memcpy(dest1, src, sz_test2));
  if (_i == 2)
    ck_assert_pstr_eq(s21_memcpy(dest2, src, 1), memcpy(dest2, src, 1));
}
END_TEST

// 4    Тестирование функции s21_memset
START_TEST(s21_memset_test01) {
  char str1[] = "Some test text";
  char str2[] = "";
  int ch = 'x';
  int index1 = 5;
  // int index2 = 10;
  if (_i == 0)
    ck_assert_pstr_eq(s21_memset(str1, ch, index1), memset(str1, ch, index1));
  // По идее работать не должно но работает при index2 меньше длины str1
  if (_i == 1) ck_assert_pstr_eq(s21_memset(str2, ch, 1), memset(str2, ch, 1));
}
END_TEST

Suite *suite_mem_create(void) {
  Suite *suite = suite_create("\n-- S21_MEMORY functions tests --");
  TCase *mem_func_tests = tcase_create("\n- s21_memory functions test cases");

  tcase_add_loop_test(mem_func_tests, s21_memchr_test04, 0, 5);
  tcase_add_loop_test(mem_func_tests, s21_memcmp_test05, 0, 6);
  tcase_add_loop_test(mem_func_tests, s21_memcpy_test02, 0, 3);
  tcase_add_loop_test(mem_func_tests, s21_memset_test01, 0, 2);

  suite_add_tcase(suite, mem_func_tests);

  return suite;
}