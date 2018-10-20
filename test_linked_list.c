#include "linked_list.h"
#include "test.h"

#include <assert.h>
#include <stdio.h>

int test_add_and_search() {
  printf("test_add_and_search:\n");

  LinkedList* l = ll_init();
  for(int i=0; i<50; i++)
    l = ll_add(l, i);
  for(int i=49; i>=0; i--) {
    if(!ll_search(l, i))
      return 0;
  }
  ll_destroy(l);

  printf("Passed\n\n");
  return 1;
}

int test_add_same_twice() {
  printf("test_add_same_twice:\n");

  LinkedList* l = ll_init();
  l = ll_add(l, 0);
  l = ll_add(l, 0);
  if(l->next != NULL)
    return 0;
  if(!ll_search(l, 0))
    return 0;
  ll_destroy(l);

  printf("Passed\n\n");
  return 1;
}

int test_remove_last_element() {
  printf("test_remove_last_element:\n");

  LinkedList* l = ll_init();
  for(int i=0; i<5; i++)
    l = ll_add(l, i);
  for(int i=4; i>=0; i--)
    l = ll_remove(l, i);
  if(l != NULL)
    return 0;
  ll_destroy(l);

  printf("Passed\n\n");
  return 1;
}

int test_remove_head() {
  printf("test_remove_head:\n");

  LinkedList* l = ll_init();
  for(int i=0; i<5; i++)
    l = ll_add(l, i);
  l = ll_remove(l, 0);
  if(!(l->id == 1))
    return 0;
  ll_destroy(l);

  printf("Passed\n\n");
  return 1;
}


int test_remove_mid_and_search() {
  printf("test_remove_mid_and_search:\n");

  LinkedList* l = ll_init();
  for(int i=0; i<10; i++)
    l = ll_add(l, i);
  l = ll_remove(l, 5);
  if(ll_search(l, 5))
    return 0;
  if(!ll_search(l, 9))
     return 0;
  ll_destroy(l);

  printf("Passed\n\n");
  return 1;
}
  
int test_remove_tail_and_search() {
  printf("test_remove_mid_and_search:\n");

  LinkedList* l = ll_init();
  for(int i=0; i<5; i++)
    l = ll_add(l, i);
  l = ll_remove(l, 4);
  l = ll_add(l, 5);
  if(ll_search(l, 4))
    return 0;
  if(!ll_search(l, 5))
     return 0;
  ll_destroy(l);

  printf("Passed\n\n");
  return 1;
}

int test_print() {
  printf("test_print:\n");

  LinkedList* l = ll_init();
  for(int i=0; i<5; i++)
    l = ll_add(l, i);
  printf("Expected output:\n");
  printf("0-> 1-> 2-> 3-> 4\n\n");
  printf("Actual ouput:\n");
  ll_print(l);
  printf("\n");
  ll_destroy(l);

  printf("Passed\n\n");
  return 1;
}

int test_add_malloc_fails_head() {
  printf("test_add_malloc_fails_head:\n");

  MALLOC_CALLS = 0;
  LinkedList* l = ll_init();
  if(ll_add(l, 1) != NULL)
    return 0;

  printf("Passed\n\n");
  return 1;
}


int test_add_malloc_fails_tail() {
  printf("test_add_malloc_fails_tail:\n");

  MALLOC_CALLS = 5;
  LinkedList* l = ll_init();
  for(int i=0; i<5; i++) {
    l = ll_add(l, i);
    if(l == NULL)
      return 0;
  }
  if(ll_add(l, 5) != NULL)
    return 0;

  printf("Passed\n\n");
  return 1;
}

int main() {
  MALLOC_CALLS = -1;
  int total_tests = 9;
  int passed_tests = 0;

  passed_tests += test_add_and_search();
  passed_tests += test_add_same_twice();
  passed_tests += test_remove_last_element();
  passed_tests += test_remove_head();
  passed_tests += test_remove_mid_and_search();
  passed_tests += test_remove_tail_and_search();
  passed_tests += test_print();
  passed_tests += test_add_malloc_fails_head();
  passed_tests += test_add_malloc_fails_tail();

  printf("Passed tests: %d/%d\n", passed_tests, total_tests);
  if(total_tests == passed_tests) {
    return 0;
  } else {
    return 1;
  }
}

