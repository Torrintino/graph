#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* __real_malloc(size_t size);
void* __wrap_malloc(size_t size) {
  if(MALLOC_CALLS == 0)
    return NULL;
  if(MALLOC_CALLS > 0)
    MALLOC_CALLS--;
  return __real_malloc(size);
}


void* __real_realloc(size_t size);
void* __wrap_realloc(size_t size) {
  if(MALLOC_CALLS == 0)
    return NULL;
  if(MALLOC_CALLS > 0)
    MALLOC_CALLS--;
  return __real_realloc(size);
}

void test_init() {
  turn_malloc_on();
  tests_run = 0;
  tests_passed = 0;
}

void turn_malloc_on() {
  MALLOC_CALLS = -1;
}

void turn_malloc_off(unsigned int n) {
  MALLOC_CALLS = n;
}

int test_finish() {
  printf("Passed tests: %d/%d\n", tests_passed, tests_run);
  return tests_passed == tests_run;
}
