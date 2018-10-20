#include "linked_list.h"
#include "test.h"

#include <assert.h>

int main() {
  MALLOC_CALLS = -1;
  LinkedList* l = ll_init();
  l = ll_add(l, 1);
  l = ll_add(l, 1);
  l = ll_add(l, 2);
  l = ll_add(l, 3);
  ll_print(l);
  l = ll_remove(l, 2);
  assert(!ll_search(l, 2));
  assert(ll_search(l, 3));
  ll_print(l);
  
  ll_destroy(l);
}
