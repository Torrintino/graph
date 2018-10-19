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
