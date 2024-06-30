#include "test.h"

int main() {
  int failed_count = 0;
  int passed_count = 0;
  Suite *suite_mem = suite_mem_create();
  Suite *suite_string = suite_string_create();
  Suite *suite_csharp = suite_csharp_create();
  Suite *suite_strintf = suite_sprintf_create();

  SRunner *suite_mem_runner = srunner_create(suite_mem);
  SRunner *suite_string_runner = srunner_create(suite_string);
  SRunner *suite_csharp_runner = srunner_create(suite_csharp);
  SRunner *suite_sprintf_runner = srunner_create(suite_strintf);

  srunner_run_all(suite_mem_runner, CK_NORMAL);
  failed_count += srunner_ntests_failed(suite_mem_runner);
  passed_count += srunner_ntests_run(suite_mem_runner) - failed_count;
  srunner_free(suite_mem_runner);

  srunner_run_all(suite_string_runner, CK_NORMAL);
  failed_count += srunner_ntests_failed(suite_string_runner);
  passed_count += srunner_ntests_run(suite_string_runner) - failed_count;
  srunner_free(suite_string_runner);

  srunner_run_all(suite_csharp_runner, CK_NORMAL);
  failed_count += srunner_ntests_failed(suite_csharp_runner);
  passed_count += srunner_ntests_run(suite_csharp_runner) - failed_count;
  srunner_free(suite_csharp_runner);

  srunner_run_all(suite_sprintf_runner, CK_NORMAL);
  failed_count += srunner_ntests_failed(suite_sprintf_runner);
  passed_count += srunner_ntests_run(suite_sprintf_runner) - failed_count;
  srunner_free(suite_sprintf_runner);

  printf("\n --- SUMMARY ---");
  printf("\nPASSED TESTS: %d", passed_count);
  printf("\nFAILED TESTS: %d\n", failed_count);

  return 0;
}