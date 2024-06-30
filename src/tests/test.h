#ifndef SRC_TEST_H
#define SRC_TEST_H

#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

Suite *suite_mem_create(void);
Suite *suite_string_create(void);
Suite *suite_csharp_create(void);
Suite *suite_sprintf_create(void);

#endif