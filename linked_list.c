#include "linked_list.h"

#include <stdio.h>
#include <stdlib.h>


LinkedList* ll_init() {
  return NULL;
}

LinkedList* ll_add(LinkedList* l, unsigned long id) {
  LinkedList* entry = l;

  if(entry == NULL) {
    entry = malloc(sizeof(LinkedList));
    if(entry == NULL) return NULL;
    entry->next = NULL;
    entry->id = id;
    return entry;
  }
  
  while(entry->next != NULL) {
    #ifndef LINKED_LIST_UNIQUE
    if(entry->id == id)
      return l;
    #endif
    entry = entry->next;
  }
  if(entry->id == id) return l;
  
  entry->next = malloc(sizeof(LinkedList));
  if(entry->next == NULL) {
    ll_destroy(l);
    return NULL;
  }

  entry->next->next = NULL;
  entry->next->id = id;
  return l;
}

LinkedList* ll_remove(LinkedList* l, unsigned long id) {
  if(l == NULL) return l;
  
  LinkedList* prev = l;
  if(l->id == id) {
    l = l->next;
    free(prev);
    return l;
  }

  LinkedList* current = l->next;
  while(current != NULL) {
    if(current->id == id) {
      prev->next = current->next;
      free(current);
      return l;
    }
    prev = current;
    current = current->next;
  }
  return l;
}

int ll_search(LinkedList* l, unsigned long id) {
  while(l != NULL) {
    if(l->id == id)
      return 1;
    l = l->next;
  }
  
  return 0;
}

void ll_print(LinkedList* l) {
  if(l != NULL) {
    printf("%lu", l->id);
    l = l->next;
  }
  
  while(l != NULL) {
    printf("-> %lu", l->id);
    l = l->next;
  }
  printf("\n");
}

void ll_destroy(LinkedList* l) {
  LinkedList* prev;
  while(l != NULL) {
    prev = l;
    l = l->next;
    free(prev);
  }
}
