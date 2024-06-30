#include "test.h"

// 16    Тестирование функции s21_insert
START_TEST(s21_insert_test02) {
  char src_test1[] = "Text, moe, one";
  char str_test1[] = "plus";
  char* res_test1 = s21_NULL;
  int si_test1 = 6;
  char src_test2[] = "Text,moe,one";
  char* str_test2 = s21_NULL;
  int si_test2 = 3;
  char src_test3[] = "Text.moe\0one";
  char str_test3[] = "test";
  int si_test3 = 20;
  if (_i == 0) {
    res_test1 = s21_insert(src_test1, str_test1, si_test1);
    ck_assert_pstr_eq(res_test1, "Text, plusmoe, one");
    if (res_test1 != s21_NULL) free(res_test1);
  }
  if (_i == 1)
    ck_assert_pstr_eq(s21_insert(src_test2, str_test2, si_test2), s21_NULL);
  if (_i == 2)
    ck_assert_pstr_eq(s21_insert(src_test3, str_test3, si_test3), s21_NULL);
  if (_i == 3)
    ck_assert_pstr_eq(s21_insert(s21_NULL, str_test3, si_test3), s21_NULL);
}
END_TEST

// 17    Тестирование функции s21_to_lower
START_TEST(s21_to_lower_test02) {
  char src_test1[] = "TexT, mOe, onE";
  char* res1 = s21_NULL;
  char src_test2[] = "text, moe, one";
  char* res2 = s21_NULL;
  char res_test12[] = "text, moe, one";
  char src_test3[] = "TEXT\0, moe, one";
  char* res3 = s21_NULL;
  char res_test3[] = "text";
  if (_i == 0) {
    res1 = s21_to_lower(src_test1);
    ck_assert_pstr_eq(res1, res_test12);
    if (res1 != s21_NULL) free(res1);
  }
  if (_i == 1) {
    res2 = s21_to_lower(src_test2);
    ck_assert_pstr_eq(res2, res_test12);
    if (res2 != s21_NULL) free(res2);
  }
  if (_i == 2) {
    res3 = s21_to_lower(src_test3);
    ck_assert_pstr_eq(res3, res_test3);
    if (res3 != s21_NULL) free(res3);
  }
}
END_TEST

// 18    Тестирование функции s21_to_upper
START_TEST(s21_to_upper_test03) {
  char src_test1[] = "TexT, mOe, onE";
  char* res1 = s21_NULL;
  char src_test2[] = "TEXT, MOE, ONE";
  char* res2 = s21_NULL;
  char res_test12[] = "TEXT, MOE, ONE";
  char src_test3[] = "text\0, moe, one";
  char* res3 = s21_NULL;
  char res_test3[] = "TEXT";
  char* src_test4 = s21_NULL;
  char* res4 = s21_NULL;
  char* res_test4 = s21_NULL;
  if (_i == 0) {
    res1 = s21_to_upper(src_test1);
    ck_assert_pstr_eq(res1, res_test12);
    if (res1 != s21_NULL) free(res1);
  }
  if (_i == 1) {
    res2 = s21_to_upper(src_test2);
    ck_assert_pstr_eq(res2, res_test12);
    if (res2 != s21_NULL) free(res2);
  }
  if (_i == 2) {
    res3 = s21_to_upper(src_test3);
    ck_assert_pstr_eq(res3, res_test3);
    if (res3 != s21_NULL) free(res3);
  }
  if (_i == 3) {
    res4 = s21_to_upper(src_test4);
    ck_assert_pstr_eq(res4, res_test4);
    if (res4 != s21_NULL) free(res4);
  }
}
END_TEST

// 19    Тестирование функции s21_trim
START_TEST(s21_trim_test05) {
  char src_test1[] = "*&test string+=";
  char trimch_test1234[] = "*&+=";
  char* res_test1 = s21_NULL;
  char res1[] = "test string";
  char src_test2[] = "*&test str\0ing+=";
  char* res_test2 = s21_NULL;
  char res2[] = "test str";
  char* src_test3 = s21_NULL;
  char* res_test3 = s21_NULL;
  char* res3 = s21_NULL;
  char src_test4[] = "test string";
  char* res_test4 = s21_NULL;
  char res4[] = "test string";

  if (_i == 0) {
    res_test1 = s21_trim(src_test1, trimch_test1234);
    ck_assert_pstr_eq(res_test1, res1);
    if (res_test1 != s21_NULL) free(res_test1);
  }
  if (_i == 1) {
    res_test2 = s21_trim(src_test2, trimch_test1234);
    ck_assert_pstr_eq(res_test2, res2);
    if (res_test2 != s21_NULL) free(res_test2);
  }
  if (_i == 2) {
    res_test3 = s21_trim(src_test3, trimch_test1234);
    ck_assert_pstr_eq(res_test3, res3);
    if (res_test3 != s21_NULL) free(res_test3);
  }
  if (_i == 3) {
    res_test4 = s21_trim(src_test4, trimch_test1234);
    ck_assert_pstr_eq(res_test4, res4);
    if (res_test4 != s21_NULL) free(res_test4);
  }
  if (_i == 4) {
    char* res_test5 = s21_trim("src_test", s21_NULL);
    ck_assert_pstr_eq(res_test5, "src_test");
    if (res_test5 != s21_NULL) free(res_test5);
  }
  if (_i == 5) {
    char* res_test5 = s21_trim(s21_NULL, s21_NULL);
    ck_assert_pstr_eq(res_test5, s21_NULL);
    if (res_test5 != s21_NULL) free(res_test5);
  }
}
END_TEST

Suite* suite_csharp_create(void) {
  Suite* suite = suite_create("\n-- S21_CSHARP functions tests --");
  TCase* csharp_func_tests = tcase_create("\n- s21_csharp test cases");

  tcase_add_loop_test(csharp_func_tests, s21_insert_test02, 0, 4);
  tcase_add_loop_test(csharp_func_tests, s21_to_lower_test02, 0, 3);
  tcase_add_loop_test(csharp_func_tests, s21_to_upper_test03, 0, 4);
  tcase_add_loop_test(csharp_func_tests, s21_trim_test05, 0, 6);

  suite_add_tcase(suite, csharp_func_tests);

  return suite;
}