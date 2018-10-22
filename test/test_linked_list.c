#include "../linked_list.h"
#include "test.h"

#include <stdio.h>

#define LINKED_LIST_UNIQUE

int test_add_and_search() {
  LinkedList* l = ll_init();
  for(int i=0; i<50; i++)
    l = ll_add(l, i);
  for(int i=49; i>=0; i--) {
    _assert(ll_search(l, i));
  }
  ll_destroy(l);
  
  return 1;
}

int test_add_same_twice() {
  LinkedList* l = ll_init();
  l = ll_add(l, 0);
  l = ll_add(l, 0);
  _assert(l->next == NULL);
  _assert(ll_search(l, 0));
  ll_destroy(l);
  
  return 1;
}

int test_remove_last_element() {
  LinkedList* l = ll_init();
  for(int i=0; i<5; i++)
    l = ll_add(l, i);
  for(int i=4; i>=0; i--)
    l = ll_remove(l, i);
  _assert(l == NULL);
  ll_destroy(l);
  
  return 1;
}

int test_remove_head() {
  LinkedList* l = ll_init();
  for(int i=0; i<5; i++)
    l = ll_add(l, i);
  l = ll_remove(l, 0);
  _assert(l->id == 1);
  ll_destroy(l);
  
  return 1;
}


int test_remove_mid_and_search() {
  LinkedList* l = ll_init();
  for(int i=0; i<10; i++)
    l = ll_add(l, i);
  l = ll_remove(l, 5);
  _assert(!ll_search(l, 5));
  _assert(ll_search(l,9));
  ll_destroy(l);
  
  return 1;
}
  
int test_remove_tail_and_search() {
  LinkedList* l = ll_init();
  for(int i=0; i<5; i++)
    l = ll_add(l, i);
  l = ll_remove(l, 4);
  l = ll_add(l, 5);
  _assert(!ll_search(l, 4));
  _assert(ll_search(l, 5));
  ll_destroy(l);
  
  return 1;
}

int test_print() {
  LinkedList* l = ll_init();
  for(int i=0; i<5; i++)
    l = ll_add(l, i);
  printf("Expected output:\n");
  printf("0-> 1-> 2-> 3-> 4\n\n");
  printf("Actual ouput:\n");
  ll_print(l);
  printf("\n");
  ll_destroy(l);
  
  return 1;
}

int test_add_malloc_fails_head() {
  turn_malloc_off(0);
  LinkedList* l = ll_init();
  _assert(ll_add(l, 1) == NULL);
  
  return 1;
}


int test_add_malloc_fails_tail() {
  turn_malloc_off(5);
  
  LinkedList* l = ll_init();
  for(int i=0; i<5; i++) {
    l = ll_add(l, i);
    if(l == NULL)
      return 0;
  }
  _assert(ll_add(l, 5) == NULL);
  
  return 1;
}

int main() {
  printf("test_linked_lists:\n");
  test_init();

  _verify(test_add_and_search);
  _verify(test_add_same_twice);
  _verify(test_remove_last_element);
  _verify(test_remove_head);
  _verify(test_remove_mid_and_search);
  _verify(test_remove_tail_and_search);
  _verify(test_print);
  _verify(test_add_malloc_fails_head);
  _verify(test_add_malloc_fails_tail);

  if(!test_finish()) {
    return 1;
  }
  return 0;
}

